
// My functions
void clean() {
  for (uint8_t i = 0; i < N; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
}

void fillFromCenter() {
  
  posF = (posF + diffPos*delta);
  uint8_t pos = uint8_t(posF);
    
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

}


void fromCenter() {


  uint8_t pos = uint8_t(posF);
  for (uint8_t i = 0; i < N; i++) {
    if(i == N/2 + pos -1 || i == N/2 + pos || i == N/2 + pos +1
    || i == N/2 - pos -1 || i == N/2 - pos || i == N/2 - pos +1)
      strip.setPixelColor(i, strip.Color(0, 0, 0));
  }


  posF = (posF + diffPos*delta);

  while (posF > N/2)
    posF = posF - N/2;

  pos = uint8_t(posF); 

  for (uint8_t i = 0; i < N; i++) {
    if(i == N/2 + pos -1 || i == N/2 + pos || i == N/2 + pos +1 
    || i == N/2 - pos -1 || i == N/2 - pos || i == N/2 - pos +1)
      strip.setPixelColor(i, strip.Color(255, 0, 0));
  }

}

void ambiance() {

  k += sign;

  if (k >= KK) {
    sign = -1;
  }
  
  if (k <= 0) {
    rr = random(255);
    bb = random(255);
    sign = 1;
  }


  for (uint16_t i = 0; i < N; i++) {
    strip.setPixelColor(i, strip.Color(rr * k / KK, 0, bb * k / KK) );
  }


}

void ambianceT() {

  for (uint16_t i = 0; i < N; i++) {
    strip.setPixelColor(i, strip.Color(rT, gT, bT) );
  }


}

void vroum() {

  posF = (posF + sign*diffPos*delta);

  //  if(pos > N-3) {
  //    diffPos = -1;
  //  }

  while (posF > N)
    posF = posF - N;

  if (posF < 3)
    sign = 1;

  uint8_t pos = uint8_t(posF); 
      Serial.println(posF);
  strip.setPixelColor((N + pos - 1) % N, strip.Color(255, 0, 0));
  strip.setPixelColor((N + pos    ) % N, strip.Color(255, 0, 0));
  strip.setPixelColor((N + pos + 1) % N, strip.Color(255, 0, 0));

}



void vroumContr() {

  uint8_t pos = uint8_t(posF); 
  uint8_t oldPos = uint8_t(oldPosF); 

  uint8_t pos2 = uint8_t(pos2F); 
  uint8_t oldPos2 = uint8_t(oldPos2F); 

/*
  //Clean
  strip.setPixelColor((N + oldPos - 1) % N, strip.Color(0, 0, 0));
  strip.setPixelColor((N + oldPos  ) % N, strip.Color(0, 0, 0));
  strip.setPixelColor((N + oldPos + 1) % N, strip.Color(0, 0, 0));

  strip.setPixelColor((N + oldPos - 1) % N, strip.Color(0, 0, 0));
  strip.setPixelColor((N + oldPos  ) % N, strip.Color(0, 0, 0));
  strip.setPixelColor((N + oldPos + 1) % N, strip.Color(0, 0, 0));
*/

  //Add
//  strip.setPixelColor((N + pos - 1) % N, strip.Color(255, 0, 0));
  strip.setPixelColor((N + pos  ) % N, strip.Color(255, 0, 0));
  strip.setPixelColor((N + pos + 1) % N, strip.Color(255, 0, 0));
 
//  strip.setPixelColor((N + pos2 - 1) % N, strip.Color( 55, 20,200));
  strip.setPixelColor((N + pos2  ) % N, strip.Color( 55, 20, 200));
  strip.setPixelColor((N + pos2 + 1) % N, strip.Color( 55, 20, 200));


}

void strobCtrl() {

  int t1 = floor(ratioStrobo * dureeStrobo); 
  int t2 = floor( (1-ratioStrobo) * dureeStrobo);

  if(timeRef % (t1+t2) < t1) {
    for (uint16_t i = 0; i < N; i++) {
      strip.setPixelColor(i, strip.Color(rT, gT, bT));
    }
  } else {
    for (uint16_t i = 0; i < N; i++) {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
   }
  }
}


void strobCtrlAlt() {

  int t1 = floor(ratioStrobo * dureeStrobo); 
  int t2 = floor( (1-ratioStrobo) * dureeStrobo);

  altStrobo = (altStrobo + 1)%3;
  
  if(timeRef % (t1+t2) < t1) {
    for (uint16_t i = 0; i < N; i++) {
      switch(altStrobo) {
      case 0 :strip.setPixelColor(i, strip.Color(rT,  0,  0)); break;
      case 1 :strip.setPixelColor(i, strip.Color(0 ,  0, bT)); break;
      case 2 :strip.setPixelColor(i, strip.Color(rT, gT,  0)); break;    
      }
    
    }
  } else {
    for (uint16_t i = 0; i < N; i++) {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
  
  }
}


void strob() {

  int t1 = floor(ratioStrobo * dureeStrobo); 
  int t2 = floor( (1-ratioStrobo) * dureeStrobo);
  
  if(timeRef % (60) < 20) {
    for (uint16_t i = 0; i < N; i++) {
      strip.setPixelColor(i, strip.Color(255, 255, 255));
    }
  }
}


void strobSpread() {


  int t1 = floor(ratioStrobo * dureeStrobo); 
  int t2 = floor( (1-ratioStrobo) * dureeStrobo);
  
  if(timeRef % (60) < 20) {
    
    strip.setPixelColor(0, strip.Color(255, 255, 255));
    strip.setPixelColor(1, strip.Color(255, 255, 255));
    strip.setPixelColor(2, strip.Color(255, 255, 255));

    strip.setPixelColor(N/2 - 1, strip.Color(255, 255, 255));
    strip.setPixelColor(N/2    , strip.Color(255, 255, 255));
    strip.setPixelColor(N/2 + 1, strip.Color(255, 255, 255));

    strip.setPixelColor(N - 3, strip.Color(255, 255, 255));
    strip.setPixelColor(N - 2, strip.Color(255, 255, 255));
    strip.setPixelColor(N - 1, strip.Color(255, 255, 255));
  
  }
  
}

