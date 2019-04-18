#include "nRF24L01.h" //NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24
#include "RF24.h"
#include "SPI.h"

#define SwitchPin 8 // Arcade switch is connected to Pin 8 on NANO
int SentMessage[1] = {000}; // Used to store value before being sent through the NRF24L01

RF24 radio(9,10); // NRF24L01 used SPI pins + Pin 9 and 10 on the NANO

const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01 

void setup(void){

	pinMode(SwitchPin, INPUT_PULLUP); // Define the arcade switch NANO pin as an Input using Internal Pullups
	digitalWrite(SwitchPin,HIGH); // Set Pin to HIGH at beginning

	radio.begin(); // Start the NRF24L01
	radio.openWritingPipe(pipe); // Get NRF24L01 ready to transmit
	Serial.begin(9600);
}
int a = 0;

void loop(void){

	if (digitalRead(SwitchPin) == LOW){ // If Switch is Activated
		SentMessage[0] = 111;
		radio.write(SentMessage, 1); // Send value through NRF24L01
		if(a == 1) {
			Serial.println("Switch is Activated");
			a = 0;
		}
	}
	else {
		SentMessage[0] = 000;
		radio.write(SentMessage, 1);
		if(a == 0) {
			Serial.println("Switch is not Activated");
			a = 1;
		}
	}
}
