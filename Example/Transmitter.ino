#include <nRF24L01.h>
#include <RF24.h>
#include <SPI.h>

int ReceivedMessage[12];

RF24 radio(9,10); // PIN CE dan CSN dari NRF24l01 

const uint64_t pipe = 0xE6E6E6E6E6E6; // Alamat dari NRF24l01 harus sama pengirim dan penerimanya 

struct myData {
    int satu;
    int dua;
    int tiga;
};

void setup(void){
    radio.begin();
    radio.openWritingPipe(pipe);
    Serial.begin(9600);
}

void loop(void){
    struct myData Pdata;
    Pdata.satu = analogRead(A0);
    Pdata.dua  = analogRead(A1);
    Pdata.tiga = analogRead(A2);
    radio.write(Pdata, sizeof(Pdata)); 
}
