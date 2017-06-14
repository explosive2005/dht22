#include "RF24.h"
#include <SPI.h>

RF24 radio(7,8);

int dataRX = 0;

const uint64_t pAddress = 0xABCDABCD71LL;

struct dataStruct{
  float T;
  float H;
}dhtData;

void setup() {
  // put your setup code here, to run once:
  pinMode(5,OUTPUT);

  digitalWrite(5,HIGH);

  Serial.begin(115200);

  radio.begin();

  radio.setChannel(100);

  radio.setPALevel(RF24_PA_MAX);

  radio.setDataRate(RF24_250KBPS);

  radio.openReadingPipe(1,pAddress);

  radio.startListening();

}

void loop() {
  // put your main code here, to run repeatedly:

  while(radio.available())
  {
    radio.read(&dhtData, sizeof(dhtData));
    Serial.print("Temperature: ");
    Serial.println(dhtData.T);
    Serial.print("Humidity: ");
    Serial.println(dhtData.H);
  }

  

  //delay(1000);

  //counter++;

}
