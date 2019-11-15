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
    radio.openReadingPipe(1,pipe);
    radio.startListening();
    Serial.begin(9600);
}

void loop(void){
    struct myData Pdata;
    while (radio.available())
    {
        radio.read(&Pdata, sizeof(Pdata)); 
        Serial.print("Pdata satu : ");Serial.println(Pdata.satu);
        Serial.print("Pdata dua  : ");Serial.println(Pdata.dua);
        Serial.print("Pdata tiga : ");Serial.println(Pdata.tiga);
    }
}
