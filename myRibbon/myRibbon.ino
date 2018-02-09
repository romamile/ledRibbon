#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6


// Exterieur = Jaune = Mass
Adafruit_NeoPixel strip = Adafruit_NeoPixel(100, PIN, NEO_GRB + NEO_KHZ800);

uint16_t N;

// from Center
uint8_t rr, gg, bb;

uint16_t k, KK;

uint16_t pos, diffPos;
char val; // Data received from the serial port

uint8_t mode;
 
void setup() {

  Serial.begin(9600);
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  N = strip.numPixels();

  k = 0;
  KK = 200;
  rr = random(255);
  bb = random(255);

  pos = 0;
  diffPos = 1;

  mode = 0;
}

void loop() {

Serial.println("pojpoj");

  while (Serial.available()) { // If data is available to read,
   val = Serial.read(); // read it and store it in val
   }
   if (val == '1') { clean(); mode = 0; }
   if (val == '2') { clean(); mode = 1; }
   if (val == '3') { clean(); mode = 2; }
   if (val == '4') { clean(); mode = 3; }
   if (val == '5') { clean(); mode = 4; }
   
    
  switch(mode) {
  case 0: ambiance(); break;
  case 1: strobSpread();    break;
  case 2: strob();    break;  
  case 3: vroum();    break;  
  case 4: vroum();    break;
  }
  
}

// My behaviors
void clean() {
  for (uint16_t i = 0; i < N; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
}

void ambiance() {

  k++;
  
  if(k > KK) {
    rr = random(255);
    bb = random(255);
    k = 0;
  }

  for (uint16_t i = 0; i < N; i++) {
    strip.setPixelColor(i, strip.Color(0.7*rr*(1-cos(k*2*M_PI/KK)), 0.5*bb*(1-cos(k*2*M_PI/KK)), 0) );
  }
  
  strip.show();
  delay(5);

}


void vroum() {


  strip.setPixelColor((N+pos-1)%N, strip.Color(0, 0, 0));
  strip.setPixelColor((N+pos  )%N, strip.Color(0, 0, 0));
  strip.setPixelColor((N+pos+1)%N, strip.Color(0, 0, 0));

  pos = (pos + diffPos);

//  if(pos > N-3) {
//    diffPos = -1;
//  }

  if(pos > N)
    pos = pos - N;

  if(pos < 3)
    diffPos = 1;

  strip.setPixelColor((N+pos-1)%N, strip.Color(255, 0, 0));
  strip.setPixelColor((N+pos  )%N, strip.Color(255, 0, 0));
  strip.setPixelColor((N+pos+1)%N, strip.Color(255, 0, 0));


  strip.show();
  delay(7);

}

void strobAlt() {

  for (uint16_t i = 0; i < N-1; i++) {
    strip.setPixelColor(i%2  , strip.Color(255, 255, 255));
    strip.setPixelColor(i%2+1, strip.Color(0, 0, 0));
  }
  strip.show();
  delay(50);


  for (uint16_t i = 0; i < N; i++) {
    strip.setPixelColor(i%2+1, strip.Color(255, 255, 255));
    strip.setPixelColor(i%2  , strip.Color(0, 0, 0));
  }
  strip.show();
  delay(50);

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

//  strip.setPixelColor(N/2 -1, strip.Color(255, 255, 255));
//  strip.setPixelColor(N/2   , strip.Color(255, 255, 255));
//  strip.setPixelColor(N/2 +1, strip.Color(255, 255, 255));

  strip.setPixelColor(N-3, strip.Color(0,0,0));
  strip.setPixelColor(N-2, strip.Color(0,0,0));
  strip.setPixelColor(N-1, strip.Color(0,0,0));

  strip.show();
  delay(30);


  strip.setPixelColor(0, strip.Color(0,0,0));
  strip.setPixelColor(1, strip.Color(0,0,0));
  strip.setPixelColor(2, strip.Color(0,0,0));

//  strip.setPixelColor(N/2 -1, strip.Color(0,0,0));
//  strip.setPixelColor(N/2   , strip.Color(0,0,0));
//  strip.setPixelColor(N/2 +1, strip.Color(0,0,0));

  strip.setPixelColor(N-3, strip.Color(255, 255, 255));
  strip.setPixelColor(N-2, strip.Color(255, 255, 255));
  strip.setPixelColor(N-1, strip.Color(255, 255, 255));
  strip.show();
  delay(30);

}


void fromCenterSetup() {
  rr = random(255);
  gg = random(255);
  bb = random(255);

}

void fromCenter() {

  k++;

  if(k >= N/2) {
    rr = random(255);
    gg = random(255);
    bb = random(255);
    k = 0;

    delay(1000);
  }

  for (uint16_t i = 0; i < k; i++) {
    strip.setPixelColor(N/2 + i, strip.Color(rr, gg, bb));
    strip.setPixelColor(N/2 - i, strip.Color(rr, gg, bb));
  }

  strip.show();
  delay(10);

}

// =======================================
// =======================================
// =======================================
// =======================================
// =======================================

void colorFill(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
    strip.show();
    delay(wait);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
