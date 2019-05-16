#include "nRF24L01.h"
#include "RF24.h"
#include "SPI.h"
#include "I2Cdev.h"
#include "MPU6050.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif
MPU6050 accelgyro(0x68);
int16_t ax, ay, az;
int16_t gx, gy, gz;

#define OUTPUT_READABLE_ACCELGYRO

#define LED_PIN 13
bool blinkState = false;

#define SwitchPin 8
int SentMessage[1] = {000};

RF24 radio(9, 10);

const uint64_t pipe = 0xE6E6E6E6E6E6; // Alamat NRF

const unsigned int TRIG_PIN = 5;
const unsigned int ECHO_PIN = 6;

void setup(void) {
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif

  pinMode(SwitchPin, INPUT_PULLUP);
  digitalWrite(SwitchPin, HIGH);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  radio.begin();
  radio.openWritingPipe(pipe);
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();
  Serial.begin(9600);
  Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
}
int a = 0;

void loop() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    const unsigned long duration = pulseIn(ECHO_PIN, HIGH);
    int distance = duration/29/2; // dalam cm
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    if(duration==0){
     Serial.println("Warning: no pulse from sensor");
    }
    
    #ifdef OUTPUT_READABLE_ACCELGYRO
    // display tab-separated accel/gyro x/y/z values
    Serial.print("");
    Serial.print(ax); Serial.print(",");
    Serial.print(ay); Serial.print(",");
    Serial.print(az); Serial.print(",");
    Serial.print(gx); Serial.print(",");
    Serial.print(gy); Serial.print(",");
    Serial.print(gz); Serial.print(",");
    if(distance < 1000) {
      Serial.print(distance); Serial.print("\n");
    }
    int transmitData[] = {ax, ay, az, gx, gy, gz, distance};
    radio.write(transmitData, sizeof(transmitData));
//    Serial.println(distance);
    //Serial.println(sizeof(transmitData));
  #endif

  #ifdef OUTPUT_BINARY_ACCELGYRO
    Serial.write((uint8_t)(ax >> 8)); Serial.write((uint8_t)(ax & 0xFF));
    Serial.write((uint8_t)(ay >> 8)); Serial.write((uint8_t)(ay & 0xFF));
    Serial.write((uint8_t)(az >> 8)); Serial.write((uint8_t)(az & 0xFF));
    Serial.write((uint8_t)(gx >> 8)); Serial.write((uint8_t)(gx & 0xFF));
    Serial.write((uint8_t)(gy >> 8)); Serial.write((uint8_t)(gy & 0xFF));
    Serial.write((uint8_t)(gz >> 8)); Serial.write((uint8_t)(gz & 0xFF));
  #endif
   // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
}
