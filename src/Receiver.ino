/* 
   Created by Yvan / https://Brainy-Bits.com

   This code is in the public domain...
   You can: copy it, use it, modify it, share it or just plain ignore it!
   Thx!

 */


// NRF24L01 Module Tutorial - Code for Receiver using Arduino UNO

//Include needed Libraries at beginning
#include "nRF24L01.h" // NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24
#include "RF24.h"
#include "SPI.h"

int ReceivedMessage[1] = {000}; // Used to store value received by the NRF24L01

RF24 radio(9,10); // NRF24L01 used SPI pins + Pin 9 and 10 on the UNO

const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01 

void setup(void){

	radio.begin(); // Start the NRF24L01

	radio.openReadingPipe(1,pipe); // Get NRF24L01 ready to receive

	radio.startListening(); // Listen to see if information received
	Serial.begin(9600);
	Serial.println("Beginning Received");
}

void loop(void){

	while (radio.available())
	{
		radio.read(ReceivedMessage, 1); // Read information from the NRF24L01

		if (ReceivedMessage[0] == 111) // Indicates switch is pressed
		{
			Serial.println("Switch is pressed");
		}
		else
		{
			Serial.println("Switch is turned off");
		}
		delay(10);
	}
}
