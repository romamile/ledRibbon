#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6

// TODO
/*
   concidérer qu'on envoit toujours 4 byte Et donc agire selon le message seuleemtn si on en a 4

   control de strob

*/

#include "cpt.h"

Adafruit_NeoPixel strip = Adafruit_NeoPixel(100, PIN, NEO_BRG + NEO_KHZ800);

uint16_t N;

uint8_t rr, gg, bb;
uint8_t rT, gT, bT;
uint16_t k, KK;

float posF, oldPosF;
float pos2F, oldPos2F;
cpt pos_fromCenter = cpt();

float diffPos;
int8_t sign;
uint16_t delta;

uint8_t mode, mstrMode;
byte mess[10];
byte piano[100];
int iMess;

unsigned long timeRef;


int altStrobo = 0;
float ratioStrobo = 0.5;
int dureeStrobo = 100;

void setup() {

  Serial.begin(9600);

  timeRef = micros();

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  N = strip.numPixels();

  k = 0;
  KK = 255;

  posF = 0;
  diffPos = 0.00001;
  sign = 1;
  mode = 1;

  for (uint8_t i = 0; i < 10; ++i)
    mess[i] = 0;
  iMess = 0;

  for (uint8_t i = 0; i < 100; ++i)
    piano[i] = 0;

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
 
  clean();
      
  delta = abs(timeRef - millis());
  timeRef = millis();

  while (Serial.available()) { // If data is available to read,
    byte inByte = Serial.read();

    if (inByte != 99) {
      mess[iMess] = inByte;
      iMess++;

    } else {

      if (iMess == 1) {
        if (0 <= mess[0] && mess[0] < 20) {
          diffPos = 1;
          mstrMode = 0;
          mode = uint8_t(mess[0]);
        }
      }

      if (iMess == 2) {
        switch (mess[0]) {
          case 100: mode = 0; break;
          case 101: oldPosF = posF;   posF = float(mess[1]);  break;
          case 105: oldPos2F = pos2F; pos2F = float(mess[1]); break;

          case 102: rT = uint8_t(mess[1]); break;
          case 103: gT = uint8_t(mess[1]); break;
          case 104: bT = uint8_t(mess[1]); break;

          case 106: ratioStrobo = mess[1] * (1.0 / 255) * 0.5; break;
          case 107: dureeStrobo = mess[1] * 0.001; break;

          case 113: if (mess[1] == 1) mstrMode = 1; else mstrMode = 0; break;
          case 114: if (mess[1] == 1) mstrMode = 2; else mstrMode = 0; break;
          case 115: if (mess[1] == 1) mstrMode = 3; else mstrMode = 0; break;
          case 116: if (mess[1] == 1) mstrMode = 4; else mstrMode = 0; break;

          case 120:
            piano[ int(mess[1] * 100 / 255.0)     ] = 127;
            piano[ int(mess[1] * 100 / 255.0) + 1 ] = 127;
            piano[ int(mess[1] * 100 / 255.0) + 2 ] = 127;
            piano[ int(mess[1] * 100 / 255.0) + 3 ] = 127;
            break;
          case 121:
            piano[ int(mess[1] * 100 / 255.0)     ] = 0;
            piano[ int(mess[1] * 100 / 255.0) + 1 ] = 0;
            piano[ int(mess[1] * 100 / 255.0) + 2 ] = 0;
            piano[ int(mess[1] * 100 / 255.0) + 3 ] = 0;
            break;
            //        case 113: mstrMode = 1; break;
            //        case 114: mstrMode = 2; break;
            //        case 115: mstrMode = 3; break;
            //        case 116: mstrMode = 4; break;
        }
      }


      if (iMess == 3) {
        ratioStrobo = mess[1] * (1.0 / 255) * 0.5;
        dureeStrobo = mess[2] * 1.0;
      }

      // Reset the message
      for (uint8_t i = 0; i < 10; ++i)
        mess[10] = 0;
      iMess = 0;
    }

  }

  switch (mstrMode) {
    case 1:
      for (uint8_t i = 0; i < N; i++)
        strip.setPixelColor(i, strip.Color(200, 200, 0));
      strip.show();
      break;
    case 2:
      for (uint8_t i = 0; i < N; i++)
        strip.setPixelColor(i, strip.Color(0, 200, 200));
      strip.show();
      break;
    case 3:
      for (uint8_t i = 0; i < N; i++)
        strip.setPixelColor(i, strip.Color(200, 0, 200));
      strip.show();
      break;
    case 4:
      for (uint8_t i = 0; i < N; i++)
        strip.setPixelColor(i, strip.Color(100, 100, 200));
      strip.show();
      break;
  }

  if (mstrMode == 0)
    switch (mode) {
      case 0:                    break;
      case 1:  ambianceT();      break;

      case 8:  vroumContr();     break;

      case 16:  strob();          break;
      case 17:  strobSpread();    break;
      case 18:  strobCtrl();      break;
      case 19: strobCtrlAlt();      break;

//      case 4:  vroum();          break;
//      case 6:  fromCenter();     break;
//      case 7:  fillFromCenter(); break;
//      case 1:  ambiance();       break;
    }


  // Piano
  for (uint8_t i = 0; i < N; i++) {
    if (piano[i] > 0)
      strip.setPixelColor(i, strip.Color(rT, gT, bT));
  }
  strip.show();

}


