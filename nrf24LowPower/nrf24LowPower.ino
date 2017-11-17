#include <SPI.h> //Call SPI library so you can communicate with the nRF24L01+
#include <nRF24L01.h> //nRF2401 libarary found at https://github.com/tmrh20/RF24/
#include <RF24.h> //nRF2401 libarary found at https://github.com/tmrh20/RF24/
#include <avr/sleep.h>
#include <avr/wdt.h> 

/*WDT BYTE variables for setting timer value
     WDTO_15MS, WDTO_30MS, WDTO_60MS, WDTO_120MS, WDTO_250MS, WDTO_500MS, WDTO_1S, WDTO_2S, WDTO_4S, WDTO_8S */

const int pinCE = 9; //This pin is used to set the nRF24 to standby (0) or active mode (1)
const int pinCSN = 10; //This pin is used to tell the nRF24 whether the SPI communication is a command or message to send out
RF24 wirelessSPI(pinCE, pinCSN); // Create your nRF24 object or wireless SPI connection
const uint64_t wAddress = 0xB00B1E50D2LL;              // Pipe to write or transmit on
const uint64_t rAddress = 0xB00B1E50B1LL;  //pipe to recive data on

void setup() {
  randomSeed(analogRead(0)); //create unique seed value for random number generation
  wirelessSPI.begin();            //Start the nRF24 module
  wirelessSPI.setRetries(15,10);
  wirelessSPI.openWritingPipe(wAddress);        //open writing or transmit pipe
  wirelessSPI.openReadingPipe(1,rAddress);  //open reading or recieve pipe
  wirelessSPI.stopListening(); //go into transmit mode
}

void loop() {
   byte randNumber = (byte)random(11); //generate random guess between 0 and 10 
    if (!wirelessSPI.write(&randNumber, 1)){  //if the write fails
      // delivery failed      
     }
     
   delay(30); //delay for short time in normal mode
   wirelessSPI.powerDown(); //put nRF24L01 into power down mode
   delayWDT(WDTO_30MS);   // Use WDT sleep delay function, argument is byte variable from WDT Library
   wirelessSPI.powerUp(); //power up the nRF24
}

//This function serves as a power saving delay function. The argument is a Byte type variable that is used to set the delay time
//The function sets up sleep mode in power down state. The function then sets up the WDT timer in interrupt mode and sets it.
//It then puts the Arduino to sleep for the set time. Upon wake up the WDT and sleep mode are shut off
void delayWDT(byte timer) {
  sleep_enable(); //enable the sleep capability
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); //set the type of sleep mode. Default is Idle
  ADCSRA &= ~(1<<ADEN); //Turn off ADC before going to sleep (set ADEN bit to 0)
  WDTCSR |= 0b00011000;    //Set the WDE bit and then clear it when set the prescaler, WDCE bit must be set if changing WDE bit   
  WDTCSR =  0b01000000 | timer; //Or timer prescaler byte value with interrupt selectrion bit set
  wdt_reset(); //Reset the WDT 
  sleep_cpu(); //enter sleep mode. Next code that will be executed is the ISR when interrupt wakes Arduino from sleep
  sleep_disable(); //disable sleep mode
  ADCSRA |= (1<<ADEN); //Turn the ADC back on
}

//This is the interrupt service routine for the WDT. It is called when the WDT times out. 
//This ISR must be in your Arduino sketch or else the WDT will not work correctly
ISR (WDT_vect) 
{
  wdt_disable();
   MCUSR = 0; //Clear WDT flag since it is disabled, this is optional

}  // end of WDT_vect
