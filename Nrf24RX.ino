#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9,10);
//RF24 radio(4,15);

int dataRX = 0;

const uint64_t pAddress = 0xABCDABCD71LL;

struct dataStruct{
  uint16_t T;
  uint16_t H;
}dhtData;

void setup() {
  // put your setup code here, to run once:

  //ESP.wdtDisable();

  
  
  //pinMode(8,OUTPUT);

  //digitalWrite(8,HIGH);

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
    //yield();    
    radio.read(&dhtData, sizeof(dhtData));
    float T =  dhtData.T / 100.0;
    float H = dhtData.H / 100.0;
    Serial.print("Temperature: ");
    Serial.println(T);
    Serial.print("Humidity: ");
    Serial.println(H);
  }

  

  //delay(1000);

  //counter++;

}
