#include <SPI.h>
#include <RF24.h>

// The pin to short with GND in order to trigger a send
#define BUTTON_PIN A5

const int RF_CE = 9;
const int RF_CSN = 10;
RF24 radio(RF_CE, RF_CSN);
const uint64_t pipes[2] = { 0xe7e7e7e7e7LL, 0xc2c2c2c2c2LL };
boolean buttonPinWasActive = false;
volatile unsigned long lastSendMillis = 0;

void initRadio();

void setup() {
  Serial.begin(9600);
  
  initRadio();

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Bind asynchronous handling of radio events using Interrupts/IRQs
  // Interrupt 0 equates to pin 2 on Arduino Duo and Arduino Mini Pro.
  // This should be wired to the IRQ of the RF adaptor.
  // NOTE: Recently, this was deadlocking the sketch for some reason, so I switched back to the synchronous approach
  //attachInterrupt(0 /* pin 2 of Arduino Duo and Arduino Mini Pro */, checkRadio /* callback to execute */, FALLING /* when pin goes 1 -> 0 */);
}

void loop() {

  boolean buttonPinActive = pinIsActive(BUTTON_PIN);
  boolean buttonChanged = (buttonPinActive != buttonPinWasActive);
  if (buttonChanged) {

    Serial.print("Button changed (");
    Serial.print(buttonPinActive);
    Serial.print(")\n");

    uint8_t tx_data[1];
    if (buttonPinActive) {
      // Theme 1
      tx_data[0] = 2;
    } else {
      // Theme 2
      tx_data[0] = 1;
    }
    Serial.print("Sending theme (");
    Serial.print(tx_data[0]);
    Serial.print(")\n");
    // transmit the data
    radio.stopListening();
    radio.write( &tx_data, sizeof(tx_data) );
    lastSendMillis = micros();
    radio.startListening();
  }
  buttonPinWasActive = buttonPinActive;
  
  // Handle ACKs synchrnously (not via Interrupts/IRQs)
  while (radio.available()) {
    uint8_t tx_data[1];
    radio.read(&tx_data,sizeof(tx_data));
    unsigned long duration = micros() - lastSendMillis;
    Serial.print("Ack:");
    Serial.print(tx_data[0]);
    Serial.print(" (");
    Serial.print(duration);
    Serial.print("Ms)\n");
  }
}

boolean pinIsActive(int pinNumber) {
  // NOTE: We invert the read value so we can make use of the
  // internal pull up resistors
  int pinValue = digitalRead(pinNumber);
  return (LOW == pinValue);
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

void checkRadio(void)
{
  // What happened?
  bool tx,fail,rx;
  radio.whatHappened(tx,fail,rx);

  if ( tx )
  {
     Serial.print("Send:OK\n");
  }

  if ( fail )
  {
     Serial.print("Send:Failed\n");
  }

  if ( rx )
  {
    Serial.print("Receive...\n");
    while (radio.available()) {
      uint8_t tx_data[1];
      radio.read(&tx_data,sizeof(tx_data));
      unsigned long duration = micros() - lastSendMillis;

      Serial.print("Ack:");
      Serial.print(tx_data[0]);
      Serial.print(" (");
      Serial.print(duration);
      Serial.print("Ms)\n");
    }
  }
}

