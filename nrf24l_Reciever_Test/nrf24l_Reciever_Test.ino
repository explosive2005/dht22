#include <SPI.h>
#include "RF24.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

RF24 radio(7,8); //RF24 (uint8_t _cepin, uint8_t _cspin)

int val, degree;

void setup() {
  Serial.begin(115200);
  
  uint8_t addresses[][6] = {"1Node","2Node"};

  radio.begin();

  radio.setChannel(108);

  radio.openReadingPipe(1,addresses[0]);

  radio.startListening();

  delay(1000);

  pwm.begin();
  
  pwm.setPWMFreq(60);

  yield();

}

void loop() {

  
  if(radio.available()){

    while(radio.available()){
      
      radio.read(&val,sizeof(val));
      
      degree = map(val, 0, 1023, 150, 700);

    } 

    Serial.println(val, DEC);

    pwm.setPWM(0, 0, degree);
  
  }


}
