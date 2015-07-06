#include <SPI.h>
#include <RF24.h>

// The pin to short with GND in order to trigger a send
#define BUTTON_PIN A5

#define RF_CS 9
#define RF_CSN 10
RF24 radio(RF_CS, RF_CSN);
const uint64_t pipes[2] = { 0xe7e7e7e7e7LL, 0xc2c2c2c2c2LL };
boolean buttonPinWasActive = false;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1, pipes[1]);
  radio.startListening();
  radio.printDetails();

  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  boolean buttonPinActive = pinIsActive(BUTTON_PIN);
  boolean buttonChanged = (buttonPinActive != buttonPinWasActive);
  if (buttonChanged) {
    uint8_t tx_data[1];
    if (buttonPinActive) {
      // Theme 1
      tx_data[0] = 1;
    } else {
      // Theme 2
      tx_data[0] = 2;
    }
    Serial.print("Sending theme (");
    Serial.print(tx_data[0]);
    Serial.print(")\n");
    // transmit the data
    radio.stopListening();
    radio.write( &tx_data, sizeof(tx_data) );
    radio.startListening();
  }
  buttonPinWasActive = buttonPinActive;
}

boolean pinIsActive(int pinNumber) {
  // NOTE: We invert the read value so we can make use of the
  // internal pull up resistors
  int pinValue = digitalRead(pinNumber);
  return (LOW == pinValue);
}

