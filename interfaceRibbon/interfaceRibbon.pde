import processing.serial.*;
import netP5.*;
import oscP5.*;

Serial myPort;
int val;  

//OSC
OscP5 oscP5;
NetAddress myRemoteLocation;
NetAddress mySelfLocation;

void setup() {
  
  size(200, 200);
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  
  // OSC
  oscP5 = new OscP5(this,7000);
//  myRemoteLocation = new NetAddress("127.0.0.1",9013);
//  mySelfLocation = new NetAddress("127.0.0.1",9031);
}

void draw() {
  background(255);

}

void oscEvent(OscMessage theOscMessage) {
  
  println("### received an osc message. with address pattern "+
          theOscMessage.addrPattern()+" typetag "+ theOscMessage.typetag());

  if(theOscMessage.checkAddrPattern("/2/push1")==true) {
    if(theOscMessage.checkTypetag("f")) {
      myPort.write('1');              
      println("TEST: 1 _ "  + theOscMessage.get(0).floatValue());
      return;
    }
  }
  
  if(theOscMessage.checkAddrPattern("/2/push2")==true) {
    if(theOscMessage.checkTypetag("f")) {
      myPort.write('2');              
      println("TEST: 2 _ "  + theOscMessage.get(0).floatValue());
      return;
    }
  }
  
  if(theOscMessage.checkAddrPattern("/2/push3")==true) {
    if(theOscMessage.checkTypetag("f")) {
      myPort.write('3');              
      println("TEST: 3 _ "  + theOscMessage.get(0).floatValue());
      return;
    }
  }
  
  
  if(theOscMessage.checkAddrPattern("/2/push4")==true) {
    if(theOscMessage.checkTypetag("f")) {
      myPort.write('4');              
      println("TEST: 4 _ "  + theOscMessage.get(0).floatValue());
      return;
    }
  }
  
 
}