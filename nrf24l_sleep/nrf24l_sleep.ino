
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

// Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 
RF24 radio(9,10);

// Topology
const uint64_t pipes[2] = { 0xABCDABCD71LL, 0x544d52687CLL };

const int TRANSMITTER = 1;

const int RECIEVER = 0;

int role = TRANSMITTER;

byte gotByte = 0;

byte sendByte = 12;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
 printf_begin();
  
  radio.begin();
//  radio.setAutoAck(1);                    // Ensure autoACK is enabled
//  radio.enableAckPayload();               // Allow optional ack payloads
//  radio.setRetries(0,15);                 // Smallest time between retries, max no. of retries
//  radio.setPayloadSize(1);                // Here we are sending 1-byte payloads to test the call-response speed
  radio.openWritingPipe(pipes[1]);        // Both radios listen on the same pipes by default, and switch when writing
  //radio.openReadingPipe(1,pipes[0]);
  //radio.startListening();                 // Start listening
  radio.stopListening();
  radio.printDetails();                   

}

void loop() {
  // put your main code here, to run repeatedly:

  if(role == TRANSMITTER)
  {
    //Serial.println('Transmitting');
    radio.write(&sendByte,sizeof(sendByte));
    
  }else if(role == RECIEVER)
  {
    while(radio.available())
    {
      radio.read(&gotByte, sizeof(gotByte));

      Serial.println(gotByte);
      
    }
  }

  if(Serial.available() > 0)
  {
    role = Serial.parseInt();

    if(role == RECIEVER)
    {
      Serial.println(role);
       //radio.openWritingPipe(pipes[1]);
       radio.openReadingPipe(1,pipes[0]);
       radio.startListening();
    }
    else if(role == TRANSMITTER){
      radio.stopListening();
      radio.openWritingPipe(pipes[1]);
      
    }
  }

}




















