import processing.serial.*;
import netP5.*;
import oscP5.*;

Serial myPort;
OscP5 oscP5;

void setup() {
  size(10, 10);
  
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  
  oscP5 = new OscP5(this, 7000);
}

void draw() {
  background(0);
  
  if ( myPort.available() > 0) {
    println("Received: " + myPort.read());
  }

}

void keyPressed() {
 byte[] sendMe = new byte[3];
      
  switch(key) {
  case 'a':
      sendMe[0] = 113;
      sendMe[1] = 1;
      sendMe[2] = 99;
      myPort.write(sendMe);
      break;
  case 'z':
      sendMe[0] = 114;
      sendMe[1] = 1;
      sendMe[2] = 99;
      myPort.write(sendMe);
      break;
  case 'e':
      sendMe[0] = 115;
      sendMe[1] = 1;
      sendMe[2] = 99;
      myPort.write(sendMe);
      break;
  case 'r':
      sendMe[0] = 116;
      sendMe[1] = 1;
      sendMe[2] = 99;
      myPort.write(sendMe);
      break;
  }
  
}


void keyReleased() {
 byte[] sendMe = new byte[3];
      
  switch(key) {
  case 'a':
      sendMe[0] = 113;
      sendMe[1] = 0;
      sendMe[2] = 99;
      myPort.write(sendMe);
      break;
  case 'z':
      sendMe[0] = 114;
      sendMe[1] = 0;
      sendMe[2] = 99;
      myPort.write(sendMe);
      break;
  case 'e':
      sendMe[0] = 115;
      sendMe[1] = 0;
      sendMe[2] = 99;
      myPort.write(sendMe);
      break;
  case 'r':
      sendMe[0] = 116;
      sendMe[1] = 0;
      sendMe[2] = 99;
      myPort.write(sendMe);
      break;
  }
  
}

void oscEvent(OscMessage theOscMessage) {
  
  println("# OSC address " + theOscMessage.addrPattern() + " typetag "+ theOscMessage.typetag());

  
  if(theOscMessage.checkAddrPattern("/2/push1") && theOscMessage.get(0).floatValue() == 1) {
    byte[] sendMe = new byte[2];
    sendMe[0] = 1;
    sendMe[1] = 99;
    myPort.write(sendMe);
    return;
  }
  
  if(theOscMessage.checkAddrPattern("/2/push2") && theOscMessage.get(0).floatValue() == 1) {
    byte[] sendMe = new byte[2];
    sendMe[0] = 2;
    sendMe[1] = 99;
    myPort.write(sendMe);
    return;
  }
  
  if(theOscMessage.checkAddrPattern("/2/push3") && theOscMessage.get(0).floatValue() == 1) {
    byte[] sendMe = new byte[2];
    sendMe[0] = 3;
    sendMe[1] = 99;
    myPort.write(sendMe);
    return;
  }
  
  
  if(theOscMessage.checkAddrPattern("/2/push4") && theOscMessage.get(0).floatValue() == 1) {
    byte[] sendMe = new byte[2];
    sendMe[0] = 4;
    sendMe[1] = 99;
    myPort.write(sendMe);
    return;
  }
  
  
  if(theOscMessage.checkAddrPattern("/2/push5") && theOscMessage.get(0).floatValue() == 1) {
      byte[] sendMe = new byte[2];
      sendMe[0] = 5;
      sendMe[1] = 99;
      myPort.write(sendMe);
      return;
  }
   
    
  if(theOscMessage.checkAddrPattern("/2/push6") && theOscMessage.get(0).floatValue() == 1) {
      byte[] sendMe = new byte[2];
      sendMe[0] = 6;
      sendMe[1] = 99;
      myPort.write(sendMe);
      return;
  }
  
    
  if(theOscMessage.checkAddrPattern("/2/push7") && theOscMessage.get(0).floatValue() == 1) {
      byte[] sendMe = new byte[2];
      sendMe[0] = 7;
      sendMe[1] = 99;
      myPort.write(sendMe);
      return;
  }
   
    
  if(theOscMessage.checkAddrPattern("/2/push8") && theOscMessage.get(0).floatValue() == 1) {
      byte[] sendMe = new byte[2];
      sendMe[0] = 8;
      sendMe[1] = 99;
      myPort.write(sendMe);
      return;
  }
  
  if(theOscMessage.checkAddrPattern("/2/push9") && theOscMessage.get(0).floatValue() == 1) {
      byte[] sendMe = new byte[2];
      sendMe[0] = 9;
      sendMe[1] = 99;
      myPort.write(sendMe);
      return;
  }
  
   
  if(theOscMessage.checkAddrPattern("/2/push13")) {
      byte[] sendMe = new byte[3];
      sendMe[0] = 113;
      if(theOscMessage.get(0).floatValue() == 0) sendMe[1] = 0; else sendMe[1] = 1;
      sendMe[2] = 99;
      myPort.write(sendMe);
      return;
  }

     
  if(theOscMessage.checkAddrPattern("/2/push14")) {
      byte[] sendMe = new byte[3];
      sendMe[0] = 114;
      if(theOscMessage.get(0).floatValue() == 0) sendMe[1] = 0; else sendMe[1] = 1;
      sendMe[2] = 99;
      myPort.write(sendMe);
      return;
  }

   
  if(theOscMessage.checkAddrPattern("/2/push15")) {
      byte[] sendMe = new byte[3];
      sendMe[0] = 115;
      if(theOscMessage.get(0).floatValue() == 0) sendMe[1] = 0; else sendMe[1] = 1;
      sendMe[2] = 99;
      myPort.write(sendMe);
      return;
  }

   
  if(theOscMessage.checkAddrPattern("/2/push16")) {
      byte[] sendMe = new byte[3];
      sendMe[0] = 116;
      if(theOscMessage.get(0).floatValue() == 0) sendMe[1] = 0; else sendMe[1] = 1;
      sendMe[2] = 99;
      myPort.write(sendMe);
      return;
  }

  
  if(theOscMessage.checkAddrPattern("/1/fader5")) {
    byte a = byte(theOscMessage.get(0).floatValue()*100);
    byte[] sendMe = new byte[3];
    sendMe[0] = 101;
    sendMe[1] = a;
    sendMe[2] = 99;
    myPort.write(sendMe);
    return;
  }
   
  if(theOscMessage.checkAddrPattern("/1/fader1")) {
    byte a = byte(theOscMessage.get(0).floatValue()*255);
    byte[] sendMe = new byte[3];
    sendMe[0] = 102;
    sendMe[1] = a;
    sendMe[2] = 99;
    myPort.write(sendMe);
    return;
  }
   
  if(theOscMessage.checkAddrPattern("/1/fader2")) {
    byte a = byte(theOscMessage.get(0).floatValue()*255);
    byte[] sendMe = new byte[3];
    sendMe[0] = 103;
    sendMe[1] = a;
    sendMe[2] = 99;
    myPort.write(sendMe);
    return;
  }
   
  if(theOscMessage.checkAddrPattern("/1/fader3")) {
    byte a = byte(theOscMessage.get(0).floatValue()*255);
    byte[] sendMe = new byte[3];
    sendMe[0] = 104;
    sendMe[1] = a;
    sendMe[2] = 99;
    myPort.write(sendMe);
    return;
  }
     
  if(theOscMessage.checkAddrPattern("/3/xy")) {
    byte a = byte(theOscMessage.get(0).floatValue()*255);
    byte b = byte(theOscMessage.get(1).floatValue()*255);
    byte[] sendMe = new byte[4];
    sendMe[0] = 105;
    sendMe[1] = a;
    sendMe[2] = b;
    sendMe[3] = 99;
    myPort.write(sendMe);
    return;
  }
 
}