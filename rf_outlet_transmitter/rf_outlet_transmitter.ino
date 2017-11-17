#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
 Serial.begin(9600);

 // Transmitter is connected to Arduino Pin #10 
 mySwitch.enableTransmit(10);

 // Optional set pulse length.
 mySwitch.setPulseLength(186);

 // set protocol (default is 1, will work for most outlets)
  //mySwitch.setProtocol(1);

 // Optional set number of transmission repetitions.
 // mySwitch.setRepeatTransmit(15);

 pinMode(13,OUTPUT);

}

void loop() {
 mySwitch.send("010101000111010100000011");
 digitalWrite(13,HIGH);
 delay(500);
 digitalWrite(13,LOW);
 delay(1000); 
 mySwitch.send("010101000111010100001100");
 digitalWrite(13,HIGH);
 delay(500);
 digitalWrite(13,LOW);
 delay(1000); 
 
}
