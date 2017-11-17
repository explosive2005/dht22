#include <SPI.h>
#include "RF24.h"

RF24 radio(9,10); //RF24 (uint8_t _cepin, uint8_t _cspin)

unsigned long startTime, endTime = 0;

int val = 0;

void setup() {
  Serial.begin(115200);
  pinMode(A2, INPUT);
  
  uint8_t addresses[][6] = {"1Node","2Node"};

 radio.begin();

    radio.setChannel(100);

    radio.setRetries(8, 15);

    radio.setDataRate(RF24_250KBPS);
    
    radio.setPALevel(RF24_PA_MAX);

  radio.openWritingPipe(addresses[0]);

  delay(1000);
  

}

void loop() {
  

  //startTime = micros();

  //val = analogRead(A2);
  
/*
  for(int i = 13; i<=16; i++)
  {
    
    
    val = i;

    radio.write(&val, sizeof(val));  

 
  }

  
 delay(1000);
   
 */
 

  while(Serial.available()>2)
  {
    val = Serial.parseInt();

    if(radio.write(&val, sizeof(val))){
      
      Serial.println(val);
    }else
    {
      Serial.println("Message Not Recieved");
    }

   
  }


  
 
 
  
  
  //delay(1000);

  // put your main code here, to run repeatedly:

}
