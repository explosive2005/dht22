#include "RF24.h"
#include <SPI.h>
//#include "LowPower.h"
#include "DHT.h"
#include <avr/wdt.h> //Watch dog timer functions
#include <avr/sleep.h>
#include <avr/power.h>


DHT dht(3, DHT22);

RF24 radio(9,10);

int counter = 0;

const uint64_t pAddress = 0xABCDABCD71LL;
//
struct dataStruct{
  uint16_t T;
  uint16_t H;
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

void goSleep()
{
  sleep_enable(); //enable the sleep mode
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); //set the type of sleep mode. Default is Idle. power down saves the most power
  ADCSRA &= ~(1<<ADEN); //Turn off ADC before going to sleep (set ADEN bit to 0). this saves even more power
  WDTCSR = (24);//change enable and WDE - also resets
  WDTCSR = (33);//prescalers only - get rid of the WDE and WDCE bit
  WDTCSR = (64);//enable interrupt mode
  wdt_reset(); //Reset the WDT 
  sleep_cpu(); //enter sleep mode. Next code that will be executed is the ISR when interrupt wakes Arduino from sleep
  sleep_disable(); //disable sleep mode
  ADCSRA |= (1<<ADEN); //Turn the ADC back on
}

void enableWDT()
{
  wdt_disable(); //disable wdt just in case the time is about run out

  WDTCSR = (24); //enable wdt

  WDTCSR = (32); //set wdt timer for 4 sec

  WDTCSR = 0b01001000;//enable interrupt mode

  //wdt_reset();
  
}

ISR(WDT_vect){
  //DON'T FORGET THIS!  Needed for the watch dog timer.  This is called after a watch dog timer timeout - this is the interrupt function called after waking up
}// watchdog interrupt

void loop() {
  // put your main code here, to run repeatedly:
 
  //LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  radio.powerDown();

  goSleep();

  radio.powerUp();

  //enableWDT();

  delay(1000);

  dhtData.T = dht.readTemperature(true) * 100;

  dhtData.H = dht.readHumidity() * 100;
 
  radio.write(&dhtData, sizeof(dhtData));

  //wdt_reset();

  //Serial.println(T);
  
  //Serial.println(dhtData.H);

}
