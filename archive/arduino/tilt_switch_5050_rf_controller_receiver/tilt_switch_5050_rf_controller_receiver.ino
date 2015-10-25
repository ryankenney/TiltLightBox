// RF Receiver

#include <SPI.h>
#include <RF24.h>

#define RF_CS 9
#define RF_CSN 10
RF24 radio(RF_CS, RF_CSN);
const uint64_t pipes[2] = { 0xe7e7e7e7e7LL, 0xc2c2c2c2c2LL };
 
struct sensor_struct{
  int sensor_id;
  float temp;
  float soil_temp;
  float humid;
  float pres;
};

const int ledPinRed = 3;
const int ledPinBlue = 5;
const int ledPinGreen = 6;
 
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipes[1]);    // note that our pipes are the same above, but that
  radio.openReadingPipe(1, pipes[0]); // they are flipped between rx and tx sides.
  radio.startListening();
  radio.printDetails();

  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinBlue, OUTPUT);
}

void writeColor(int r, int g, int b) {
  Serial.print("[");
  Serial.print(r);
  Serial.print(":");
  Serial.print(g);
  Serial.print(":");
  Serial.print(b);
  Serial.print("]");
  Serial.println();
  analogWrite(ledPinRed, r);
  analogWrite(ledPinGreen, g);
  analogWrite(ledPinBlue, b);
}

void loop() {
  if (radio.available()) {
 
    Serial.println("--------------------------------------------------------------------------------");
    uint8_t rx_data[32];  // we'll receive a 32 byte packet
    
    bool done = false;
    while (!done) {
      done = radio.read( &rx_data, sizeof(rx_data) );
      printf("Got payload @ %lu...\r\n", millis());
    }
    
    // echo it back real fast
    radio.stopListening();
    radio.write( &rx_data, sizeof(rx_data) );
    Serial.println("Sent response.");
    radio.startListening();
 
    // do stuff with the data we got.
    writeColor(rx_data[0], rx_data[1], rx_data[2]);
  }
}

