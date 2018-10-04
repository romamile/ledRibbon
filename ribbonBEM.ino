#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// C function showing how to do time delay 
#include <stdio.h> 
// To use time library of C 
#include <time.h> 

#define PIN 6


// Exterieur = Jaune = Mass
Adafruit_NeoPixel strip = Adafruit_NeoPixel(300, PIN, NEO_GRB + NEO_KHZ800); //Test si NEO_RGB

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

uint16_t N;

// from Center
uint8_t rr, gg, bb;

uint16_t k, KK;

uint16_t pos, oldPos, diffPos;
String inputString = "";

uint8_t mode;

//SDL_Event event;
//int continuer = 1;
//int tempsPrecedent = 0, tempsActuel = 0;


void setup() {

  Serial.begin(9600);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  N = strip.numPixels()/12;

  k = 0;
  KK = 200;
  rr = random(255);
  bb = random(255);

  pos = 0;
  diffPos = 1;

  mode = 6;
  inputString.reserve(200);

  pinMode(PIN, OUTPUT);

  //digitalWrite(PIN, LOW);
}

void loop() {

  digitalWrite(LED_BUILTIN, HIGH);
  //LED_BUILTIN = led orange sur arduino
  
  inputString = "";

  while (Serial.available()) { // If data is available to read,
    char inChar = (char)Serial.read();
    
    if(inChar != '\n') {
      inputString += inChar;
      
    } else {

      clean();
 
      if(inputString.length() > 0) {
        byte tst = inputString.charAt(0);
        
        if( tst > 0 && tst < 17) {
          mode = (uint8_t)tst;
        }
    
      }
    }
  }
/*
 for(uint16_t i = 0; i<10; i++){
  strip.setPixelColor(i, strip.Color(100, 100, 100));
 }
 strip.show();
 delay(5);
*/

  switch (mode) {
    case 1: clean(); break;
    case 2: strobSpread();    break;
    case 3: strob();    break;
    case 4: vroum();    break;
    case 5: vroumContr();    break;
    case 6: questionReponse(); break;
    case 7: strobAlt(); break;
    case 8: fromCenterSetup(); break;
    case 9: fromCenter(); break;
    case 10: rainbow(1000); break;
    case 11: rain2(); break;
    case 12: circle(); break;
    case 13: wave1();  break;
    case 14: wave2();  break;
    case 15: waveLightClean();  break;
    case 16: rain();  break; //fait planter après ? je vais faire un code sans loop
  }
//  clean();
//  strobAlt();
//  fromCenterSetup();
//  fromCenter();
//  colorFill(uint32_t c, uint8_t wait);
//  colorWipe(uint32_t c, uint8_t wait);
//  rainbow(uint8_t wait);
//  rainbowCycle(uint8_t wait);
//  theaterChase(uint32_t c, uint8_t wait);
//  theaterChaseRainbow(uint8_t wait);
//  Wheel(byte WheelPos);
}

// My behaviors
void clean() {
  for (uint16_t i = 0; i < N; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
}

void ambiance() {

  k++;

  if (k > KK) {
    rr = random(255);
    bb = random(255);
    k = 0;
  }

  for (uint16_t i = 0; i < N; i++) {
    strip.setPixelColor(i, strip.Color(0.7 * rr * (1 - cos(k * 2 * M_PI / KK)), 0.5 * bb * (1 - cos(k * 2 * M_PI / KK)), 0) );
  }

  strip.show();
  delay(5);

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
  delay(7);




  strip.setPixelColor(pos - 1, strip.Color(0, 0, 0));
  strip.setPixelColor(pos    , strip.Color(0, 0, 0));
  strip.setPixelColor(pos + 1, strip.Color(0, 0, 0));

  pos = pos + 3;

  if (pos > N)
    pos = pos - N;

  strip.setPixelColor(pos - 1, strip.Color(255, 0, 0));
  strip.setPixelColor(pos    , strip.Color(255, 0, 0));
  strip.setPixelColor(pos + 1, strip.Color(255, 0, 0));

  strip.show();

 // delay(1);
}



void vroumContr() {

  strip.setPixelColor((N + oldPos - 1) % N, strip.Color(0, 0, 0));
  strip.setPixelColor((N + oldPos  ) % N, strip.Color(0, 0, 0));
  strip.setPixelColor((N + oldPos + 1) % N, strip.Color(0, 0, 0));


  strip.setPixelColor((N + pos - 1) % N, strip.Color(255, 0, 0));
  strip.setPixelColor((N + pos  ) % N, strip.Color(255, 0, 0));
  strip.setPixelColor((N + pos + 1) % N, strip.Color(255, 0, 0));

  strip.show();
  delay(5);

}

void vroumvroum() {


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
  
  strip.setPixelColor((N + pos + 2) % N, strip.Color(0, 0, 0));
  strip.setPixelColor((N + pos  + 3) % N, strip.Color(0, 0, 0));
  strip.setPixelColor((N + pos + 4) % N, strip.Color(0, 0, 0));

  strip.setPixelColor((N + pos + 5) % N, strip.Color(255, 0, 0));
  strip.setPixelColor((N + pos  + 6) % N, strip.Color(255, 0, 0));
  strip.setPixelColor((N + pos + 7) % N, strip.Color(255, 0, 0));
  
  strip.setPixelColor((N + pos + 8) % N, strip.Color(0, 0, 0));
  strip.setPixelColor((N + pos  + 9) % N, strip.Color(0, 0, 0));
  strip.setPixelColor((N + pos + 10) % N, strip.Color(0, 0, 0));

  strip.setPixelColor((N + pos + 11) % N, strip.Color(255, 0, 0));
  strip.setPixelColor((N + pos  + 12) % N, strip.Color(255, 0, 0));
  strip.setPixelColor((N + pos + 13) % N, strip.Color(255, 0, 0));


  strip.show();
  delay(7);

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

void strob() {


  for (uint16_t i = 0; i < N; i++) {
    strip.setPixelColor(i, strip.Color(100, 100, 100));
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

  strip.setPixelColor(N - 3, strip.Color(0, 0, 0));
  strip.setPixelColor(N - 2, strip.Color(0, 0, 0));
  strip.setPixelColor(N - 1, strip.Color(0, 0, 0));

  strip.show();
  delay(30);


  strip.setPixelColor(0, strip.Color(0, 0, 0));
  strip.setPixelColor(1, strip.Color(0, 0, 0));
  strip.setPixelColor(2, strip.Color(0, 0, 0));

  //  strip.setPixelColor(N/2 -1, strip.Color(0,0,0));
  //  strip.setPixelColor(N/2   , strip.Color(0,0,0));
  //  strip.setPixelColor(N/2 +1, strip.Color(0,0,0));

  strip.setPixelColor(N - 3, strip.Color(255, 255, 255));
  strip.setPixelColor(N - 2, strip.Color(255, 255, 255));
  strip.setPixelColor(N - 1, strip.Color(255, 255, 255));
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

  if (k >= N / 2) {
    rr = random(255);
    gg = random(255);
    bb = random(255);
    k = 0;

    delay(1000);
  }

  for (uint16_t i = 0; i < k; i++) {
    strip.setPixelColor(N / 2 + i, strip.Color(rr, gg, bb));
    strip.setPixelColor(N / 2 - i, strip.Color(rr, gg, bb));
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

// all ribbon dodgerBlue
void dodgerBlue() {
  for (uint16_t i = N; i < 2*N; i++) {
    strip.setPixelColor(i, strip.Color(30,144,255));
  }
  strip.show();
}

void push14() {
  for (uint16_t i = 0; i < N; i++) {
    strip.setPixelColor(i, strip.Color(255,255,255));
  }
  strip.show();
}

void push15() {
  for (uint16_t i = 0; i < N; i++) {
    strip.setPixelColor(i, strip.Color(255,100,0));
  }
  strip.show();
}

void push16() {
  for (uint16_t i = N; i < 2*N; i++) {
    strip.setPixelColor(i, strip.Color(100,255,100));
  }
  strip.show();
}









/****************Comportements BEM***********************/

/******** coté A*********/
void un_a() {
  for (uint16_t i = 0; i < N; i++) {
    strip.setPixelColor(i, strip.Color(100,255,100));
  }
  strip.show();
}

void deux_a() {
  for (uint16_t i = N; i < 2*N; i++) {
    strip.setPixelColor(i, strip.Color(100,255,100));
  }
  strip.show();
}

void trois_a() {
  for (uint16_t i = 2*N; i < 3*N; i++) {
    strip.setPixelColor(i, strip.Color(100,255,100));
  }
  strip.show();
}

void quattre_a() {
  for (uint16_t i = 3*N; i < 4*N; i++) {
    strip.setPixelColor(i, strip.Color(100,255,100));
  }
  strip.show();
}

void cinq_a() {
  for (uint16_t i = 4*N; i < 5*N; i++) {
    strip.setPixelColor(i, strip.Color(100,255,100));
  }
  strip.show();
}

void six_a() {
  for (uint16_t i = 5*N; i < 6*N; i++) {
    strip.setPixelColor(i, strip.Color(100,255,100));
  }
  strip.show();
}

/******** coté B*********/
void un_b() {
  for (uint16_t i = 6*N; i < 7*N; i++) {
    strip.setPixelColor(i, strip.Color(100,255,100));
  }
  strip.show();
}

void deux_b() {
  for (uint16_t i = 7*N; i < 8*N; i++) {
    strip.setPixelColor(i, strip.Color(100,255,100));
  }
  strip.show();
}

void trois_b() {
  for (uint16_t i = 8*N; i < 9*N; i++) {
    strip.setPixelColor(i, strip.Color(100,255,100));
  }
  strip.show();
}

void quattre_b() {
  for (uint16_t i = 9*N; i < 10*N; i++) {
    strip.setPixelColor(i, strip.Color(100,255,100));
  }
  strip.show();
}

void cinq_b() {
  for (uint16_t i = 10*N; i < 11*N; i++) {
    strip.setPixelColor(i, strip.Color(100,255,100));
  }
  strip.show();
}

void six_b() {
  for (uint16_t i = 11*N; i < 12*N; i++) {
    strip.setPixelColor(i, strip.Color(100,255,100));
  }
  strip.show();
}


/*************Stop****************/
void stripStop() {
  strip.show();
  delay(5);
}

void eteindre_un_a() {
  for (uint16_t i = 0; i < N; i++) {
    strip.setPixelColor(i, strip.Color(0,0,0));
  }
  strip.show();
}

void eteindre_deux_a() {
  for (uint16_t i = N; i < 2*N; i++) {
    strip.setPixelColor(i, strip.Color(0,0,0));
  }
  strip.show();
}

void eteindre_trois_a() {
  for (uint16_t i = 2*N; i < 3*N; i++) {
    strip.setPixelColor(i, strip.Color(0,0,0));
  }
  strip.show();
}

void eteindre_quattre_a() {
  for (uint16_t i = 3*N; i < 4*N; i++) {
    strip.setPixelColor(i, strip.Color(0,0,0));
  }
  strip.show();
}

void eteindre_cinq_a() {
  for (uint16_t i = 4*N; i < 5*N; i++) {
    strip.setPixelColor(i, strip.Color(0,0,0));
  }
  strip.show();
}

void eteindre_six_a() {
  for (uint16_t i = 5*N; i < 6*N; i++) {
    strip.setPixelColor(i, strip.Color(0,0,0));
  }
  strip.show();
}

/******** coté B*********/
void eteindre_un_b() {
  for (uint16_t i = 6*N; i < 7*N; i++) {
    strip.setPixelColor(i, strip.Color(0,0,0));
  }
  strip.show();
}

void eteindre_deux_b() {
  for (uint16_t i = 7*N; i < 8*N; i++) {
    strip.setPixelColor(i, strip.Color(0,0,0));
  }
  strip.show();
}

void eteindre_trois_b() {
  for (uint16_t i = 8*N; i < 9*N; i++) {
    strip.setPixelColor(i, strip.Color(0,0,0));
  }
  strip.show();
}

void eteindre_quattre_b() {
  for (uint16_t i = 9*N; i < 10*N; i++) {
    strip.setPixelColor(i, strip.Color(0,0,0));
  }
  strip.show();
}

void eteindre_cinq_b() {
  for (uint16_t i = 10*N; i < 11*N; i++) {
    strip.setPixelColor(i, strip.Color(0,0,0));
  }
  strip.show();
}

void eteindre_six_b() {
  for (uint16_t i = 11*N; i < 12*N; i++) {
    strip.setPixelColor(i, strip.Color(0,0,0));
  }
  strip.show();
}

void wave1(){

  //chaque PILLIER s'allume s'éteint successivement de derriere vers  devant
  eteindre_cinq_a();
  eteindre_cinq_b();
  eteindre_six_a();
  eteindre_six_b();
  un_a();            
  un_b();
  deux_a();
  deux_b();
  delay(50);
  eteindre_un_a();            
  eteindre_un_b();
  eteindre_deux_a();
  eteindre_deux_b();
  trois_a();
  trois_b();
  quattre_a();
  quattre_b();
  delay(50);
  eteindre_trois_a();
  eteindre_trois_b();
  eteindre_quattre_a();
  eteindre_quattre_b();
  cinq_a();
  cinq_b();
  six_a();
  six_b();
  delay(50);
  clean();
}


void wave2(){

  //chaque ARRETE s'allume s'éteint successivement de derriere vers  devant
  un_a();            
  un_b();
  delay(100);
  clean();
  deux_a();
  deux_b();
  delay(100);
  clean();
  trois_a();
  trois_b();
  delay(100);
  clean();
  quattre_a();
  quattre_b();
  delay(100);
  clean();
  cinq_a();
  cinq_b();
  delay(100);
  clean();
  six_a();
  six_b();
  delay(100);
  clean();
}

void waveLightClean(){
  //chaque arrete s'allume successivement de derriere vers devant et s'éteint successivement
  un_a();            
  un_b();
  delay(50);
  deux_a();
  deux_b();
  delay(50);
  trois_a();
  trois_b();
  delay(50);
  quattre_a();
  quattre_b();
  delay(50);
  cinq_a();
  cinq_b();
  delay(50);
  six_a();
  six_b();
  delay(50);
  eteindre_un_a();            
  eteindre_un_b();
  delay(50);
  eteindre_deux_a();
  eteindre_deux_b();
  delay(50);
  eteindre_trois_a();
  eteindre_trois_b();
  delay(50);
  eteindre_quattre_a();
  eteindre_quattre_b();
  delay(50);
  eteindre_cinq_a();
  eteindre_cinq_b();
  delay(50);
  eteindre_six_a();
  eteindre_six_b();
  delay(50);
}

void questionReponse(){

  //pilier fond gauche s'allume et s'eteind, pilier fond droite répond droite répond 0.05s plus tard
  un_a();            
  deux_a();
  delay(50);
  eteindre_un_a();            
  eteindre_deux_a();
  un_b();
  deux_b();
  delay(50);
  eteindre_un_b();
  eteindre_deux_b();
  delay(50);

  //pilier milieu gauche s'allume et s'eteind, pilier milieu droite répond droite répond 0.05s plus tard
  trois_a();
  quattre_a();
  delay(50);
  eteindre_trois_a();
  eteindre_quattre_a();
  trois_b();
  quattre_b();
  delay(50);
  eteindre_trois_b();
  eteindre_quattre_b();
  delay(50);

  //pilier devant gauche s'allume et s'eteind, pilier devant droite répond droite répond 0.05s plus tard
  cinq_a();
  six_a();
  delay(50);
  eteindre_cinq_a();
  eteindre_six_a();
  cinq_b();
  six_b();
  delay(50);
  eteindre_cinq_b();
  eteindre_six_b();
  delay(50);
}

void circle(){
  un_a();
  delay(50);
  clean();            
  deux_a();
  delay(50);
  clean();
  trois_a();
  delay(50);
  clean();
  quattre_a();
  delay(50);
  clean();
  cinq_a();
  delay(50);
  clean();
  six_a();
  delay(50);
  clean();
  six_b();
  delay(50);
  clean();
  cinq_b();
  delay(50);
  clean();
  quattre_b();
  delay(50);
  clean();
  trois_b();
  delay(50);
  clean();
  deux_b();
  delay(50);
  clean();
  un_b();
  delay(50);
  clean();
  strip.show();
}


void rain(){
  for(uint16_t i = 0;i<7*N;i++){
    if (i%N == 0){
      rainWipe(i, N);
      rainWipe(i+(6*N), N+(6*N));
      delay(1000);
    }
  }
  strip.show();
}

void rainWipe(uint16_t i, uint16_t N) {
  for (i; i < i+N; i++) {
    strip.setPixelColor(i, strip.Color(100,100,100));
    strip.show();
    delay(50);
  }
}

void rain2(){
  for(int i=0;i<7;i++){
    rainWipeGauche(i);
    rainWipeDroite(i);
    delay(1000);
  }
}

void rainWipeGauche(int i) {
  for (uint16_t j = i*N; j < (i+1)*N; j++) {
    strip.setPixelColor(j, strip.Color(100,100,100));
    strip.show();
    delay(50);
  }
}

void rainWipeDroite(int i) {
  for (uint16_t j = 6*N+(2*i)*N; j < (2*i+1)*N; j++) {
    strip.setPixelColor(j, strip.Color(100,100,100));
    strip.show();
    delay(50);
  }
}

  



