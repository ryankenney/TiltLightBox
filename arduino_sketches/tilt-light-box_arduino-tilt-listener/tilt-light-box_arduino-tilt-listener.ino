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

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipes[1]);    // note that our pipes are the same above, but that
  radio.openReadingPipe(1, pipes[0]); // they are flipped between rx and tx sides.
  radio.startListening();
  radio.printDetails();
}

void loop() {
  if (radio.available()) {
    uint8_t rx_data[1];
    bool done = false;
    while (!done) {
      done = radio.read( &rx_data, sizeof(rx_data) );
      Serial.print("Read Tilt (");
      Serial.print(rx_data[0]);
      Serial.print(") ");
      Serial.print(millis());
      Serial.print("\n");
    }
  }
}
