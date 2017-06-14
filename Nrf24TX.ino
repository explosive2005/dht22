#include "RF24.h"
#include <SPI.h>
#include "LowPower.h"
#include "DHT.h"

DHT dht(3, DHT22);

RF24 radio(9,10);

int counter = 0;

const uint64_t pAddress = 0xABCDABCD71LL;

struct dataStruct{
  float T;
  float H;
}dhtData;



void setup() {
  // put your setup code here, to run once:
  dht.begin();
  pinMode(4, OUTPUT);
  pinMode(5,OUTPUT);
  
  digitalWrite(4, HIGH);
  digitalWrite(5,HIGH);
  Serial.begin(115200);

  radio.begin();

  radio.setChannel(100);

  radio.setPALevel(RF24_PA_MAX);

  radio.setDataRate(RF24_250KBPS);

  radio.openWritingPipe(pAddress);

  radio.stopListening();

  int startingText = 12;

  delay(500);

  //radio.write(&startingText, sizeof(startingText));

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i<1; i++)
  {
  
  LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);

  }
  delay(500);

  dhtData.T = dht.readTemperature(true);  

  dhtData.H = dht.readHumidity();
  
  radio.write(&dhtData, sizeof(dhtData));

  Serial.print(dhtData.T);

  //delay(1000);

 

}
