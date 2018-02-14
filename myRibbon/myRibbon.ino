#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6


Adafruit_NeoPixel strip = Adafruit_NeoPixel(100, PIN, NEO_BRG + NEO_KHZ800);

uint16_t N;

uint8_t rr, gg, bb;
uint8_t rT, gT, bT;
uint16_t k, KK;

uint8_t pos, oldPos;
int8_t diffPos;

uint8_t mode, mstrMode;
byte mess[10];
int iMess;

float ratioStrobo = 0.5;
int dureeStrobo = 100;

void setup() {

  Serial.begin(9600);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  N = strip.numPixels();

  k = 0;
  KK = 255;

  pos = 0;
  diffPos = 1;

  mode = 1;

  for(uint8_t i = 0; i < 10; ++i)
    mess[10] = 0;
  iMess = 0;

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  while (Serial.available()) { // If data is available to read,
    byte inByte = Serial.read();

    if(inByte != 99) {
      mess[iMess] = inByte;
      iMess++;
      
    } else {
      
      clean();
      if(iMess == 1) {
        if(0 < mess[0] && mess[0] < 13) {  
          diffPos = 1;
          mstrMode = 0;
          mode = uint8_t(mess[0]);
        }    
      }

      if(iMess == 2) {
        switch(mess[0]) {
        case 101: oldPos = pos;
          pos = uint8_t(mess[1]);
          break;
          
        case 102: rT = uint8_t(mess[1]); break;
        case 103: gT = uint8_t(mess[1]); break;
        case 104: bT = uint8_t(mess[1]); break;

        case 113: if(mess[1] == 1) mstrMode = 1; else mstrMode = 0; break;
        case 114: if(mess[1] == 1) mstrMode = 2; else mstrMode = 0; break;
        case 115: if(mess[1] == 1) mstrMode = 3; else mstrMode = 0; break;
        case 116: if(mess[1] == 1) mstrMode = 4; else mstrMode = 0; break;
        
//        case 113: mstrMode = 1; break;
//        case 114: mstrMode = 2; break;
//        case 115: mstrMode = 3; break;
//        case 116: mstrMode = 4; break;
        }
      }

      
      if(iMess == 3) {
        ratioStrobo = mess[1]* (1.0 / 255);
        dureeStrobo = mess[2]* (1.0 / 255) * 400;
      }
      
      // Reset the message
      for(uint8_t i = 0; i < 10; ++i)
        mess[10] = 0;
      iMess = 0;
    }

  }

  switch(mstrMode) {
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
  
  if(mstrMode == 0)
  switch (mode) {
    case 1: ambiance();       break;
    case 2: strobSpread();    break;
    case 3: strob();          break;
    case 4: vroum();          break;
    case 5: vroumContr();     break;
    case 6: fromCenter();     break;
    case 7: fillFromCenter(); break;
    case 8: ambianceT();      break;
    case 9: strobCtrl();      break;
  }


}


// My functions
void clean() {
  for (uint8_t i = 0; i < N; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
}

void fillFromCenter() {
  
  pos = (pos + diffPos);
  if (pos > N/2) {
    pos = pos - N/2;
    rr = random(255);
    gg = random(255);
    bb = random(255);
  }
  
  for (uint8_t i = 0; i < N; i++) {
    if(i == N/2 + pos -1 || i == N/2 + pos || i == N/2 + pos +1 
    || i == N/2 - pos -1 || i == N/2 - pos || i == N/2 - pos +1)
      strip.setPixelColor(i, strip.Color(rr, gg, bb));
  }

  strip.show();

  delay(10);
}


void fromCenter() {
  
  for (uint8_t i = 0; i < N; i++) {
    if(i == N/2 + pos -1 || i == N/2 + pos || i == N/2 + pos +1
    || i == N/2 - pos -1 || i == N/2 - pos || i == N/2 - pos +1)
      strip.setPixelColor(i, strip.Color(0, 0, 0));
  }

  pos = (pos + diffPos);
  if (pos > N/2)
    pos = pos - N/2;

  for (uint8_t i = 0; i < N; i++) {
    if(i == N/2 + pos -1 || i == N/2 + pos || i == N/2 + pos +1 
    || i == N/2 - pos -1 || i == N/2 - pos || i == N/2 - pos +1)
      strip.setPixelColor(i, strip.Color(255, 0, 0));
  }

  strip.show();

  delay(10);
}

void ambiance() {

  k += diffPos;

  if (k >= KK) {
    diffPos = -1;
  }
  
  if (k <= 0) {
    rr = random(255);
    bb = random(255);
    diffPos = 1;
  }


  for (uint16_t i = 0; i < N; i++) {
    strip.setPixelColor(i, strip.Color(rr * k / KK, 0, bb * k / KK) );
  }

  strip.show();

}

void ambianceT() {

  for (uint16_t i = 0; i < N; i++) {
    strip.setPixelColor(i, strip.Color(rT, gT, bT) );
  }

  strip.show();

}

void vroum() {


  strip.setPixelColor((N + pos - 1) % N, strip.Color(0, 0, 0));
  strip.setPixelColor((N + pos    ) % N, strip.Color(0, 0, 0));
  strip.setPixelColor((N + pos + 1) % N, strip.Color(0, 0, 0));

  pos = (pos + diffPos);

  //  if(pos > N-3) {
  //    diffPos = -1;
  //  }

  if (pos > N)
    pos = pos - N;

  if (pos < 3)
    diffPos = 1;

  strip.setPixelColor((N + pos - 1) % N, strip.Color(255, 0, 0));
  strip.setPixelColor((N + pos  ) % N, strip.Color(255, 0, 0));
  strip.setPixelColor((N + pos + 1) % N, strip.Color(255, 0, 0));


  strip.show();
  delay(21);

}



void vroumContr() {

  strip.setPixelColor((N + oldPos - 1) % N, strip.Color(0, 0, 0));
  strip.setPixelColor((N + oldPos  ) % N, strip.Color(0, 0, 0));
  strip.setPixelColor((N + oldPos + 1) % N, strip.Color(0, 0, 0));

  strip.setPixelColor((N + pos - 1) % N, strip.Color(255, 0, 0));
  strip.setPixelColor((N + pos  ) % N, strip.Color(255, 0, 0));
  strip.setPixelColor((N + pos + 1) % N, strip.Color(255, 0, 0));

  strip.show();

}

void strobAlt() {

  for (uint16_t i = 0; i < N - 1; i++) {
    strip.setPixelColor(i % 2  , strip.Color(255, 255, 255));
    strip.setPixelColor(i % 2 + 1, strip.Color(0, 0, 0));
  }
  strip.show();
  delay(50);

  for (uint16_t i = 0; i < N; i++) {
    strip.setPixelColor(i % 2 + 1, strip.Color(255, 255, 255));
    strip.setPixelColor(i % 2  , strip.Color(0, 0, 0));
  }
  strip.show();
  delay(50);

}


void strobCtrl() {

  int t1 = floor(ratioStrobo * dureeStrobo); 
  int t2 = floor( (1-ratioStrobo) * dureeStrobo);
  
  for (uint16_t i = 0; i < N; i++) {
    strip.setPixelColor(i, strip.Color(rT, gT, bT));
  }
  strip.show();
  delay(t1);

  for (uint16_t i = 0; i < N; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
  delay(t2);

}


void strob() {

  for (uint16_t i = 0; i < N; i++) {
    strip.setPixelColor(i, strip.Color(255, 255, 255));
  }
  strip.show();
  delay(20);

  for (uint16_t i = 0; i < N; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
  delay(80);

}


void strobSpread() {

  strip.setPixelColor(0, strip.Color(255, 255, 255));
  strip.setPixelColor(1, strip.Color(255, 255, 255));
  strip.setPixelColor(2, strip.Color(255, 255, 255));

  strip.setPixelColor(N - 3, strip.Color(0, 0, 0));
  strip.setPixelColor(N - 2, strip.Color(0, 0, 0));
  strip.setPixelColor(N - 1, strip.Color(0, 0, 0));

  strip.show();
  delay(30);

  strip.setPixelColor(0, strip.Color(0, 0, 0));
  strip.setPixelColor(1, strip.Color(0, 0, 0));
  strip.setPixelColor(2, strip.Color(0, 0, 0));

  strip.setPixelColor(N - 3, strip.Color(255, 255, 255));
  strip.setPixelColor(N - 2, strip.Color(255, 255, 255));
  strip.setPixelColor(N - 1, strip.Color(255, 255, 255));
  strip.show();
  delay(30);

}

// DEBUG
/*
      Serial.write(101);
      for(uint8_t i = 0; i < iMess; ++i)
        Serial.write(mess[i]);

  digitalWrite(LED_BUILTIN, HIGH); delay(200);
  digitalWrite(LED_BUILTIN, LOW);  delay(200); 
  digitalWrite(LED_BUILTIN, HIGH); delay(200);
  digitalWrite(LED_BUILTIN, LOW);  delay(200); 
  digitalWrite(LED_BUILTIN, HIGH); delay(200);
  digitalWrite(LED_BUILTIN, LOW);  delay(200); 
*/      

