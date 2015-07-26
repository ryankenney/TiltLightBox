#include <SPI.h>
#include <RF24.h>

#define RF_CS 9
#define RF_CSN 10
RF24 radio(RF_CS, RF_CSN);
const uint64_t pipes[2] = { 0xe7e7e7e7e7LL, 0xc2c2c2c2c2LL };

void initRadio();
  
void setup() {
  // Init serial printing
  Serial.begin(9600);
  // Init radio
  initRadio();
}

void loop() {
  if (radio.available()) {
    uint8_t rx_data[1];
    while (radio.available()) {
      radio.read( &rx_data, sizeof(rx_data) );

      Serial.print("Recieved tilt message: ");
      Serial.print(rx_data[0]);
      Serial.print("\n");
    }
  }
}

void initRadio() {
  radio.begin();
  
  // The following settings match our node.js "nrf" usage settings
  radio.setChannel(0x4c);
  radio.setDataRate(RF24_1MBPS);
  radio.setCRCLength(RF24_CRC_16);
  radio.setRetries(15,15);
  
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1, pipes[0]);
  radio.startListening();

  // This was blocking execution on my Uno for some reason
  //radio.printDetails();
}
  
