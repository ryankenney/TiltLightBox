#include <stdio.h>
#include <stdlib.h>
#include <SPI.h>
#include <printf.h>
#include <RF24.h>
#include <tilt_light_box.h>
#include "FastLED.h"

#define NUM_LEDS 46
CRGB leds[NUM_LEDS];
const int axisPinN = A1;
const int axisPinS = A2;
const int axisPinE = 8;
const int axisPinW = 7;
const uint64_t pipes[2] = { 0xe7e7e7e7e7LL, 0xc2c2c2c2c2LL };
TiltBox* box;
const int RF_CE = 9;
const int RF_CSN = 10;
RF24 radio(RF_CE, RF_CSN);

void initRadio();
uint8_t readThemeChangeFromRF();
void mySleepFunc(unsigned long millis);
int myRandomValueFunc(int min, int max);
unsigned long myCurrentMillisFunc();
unsigned char myReceiveThemeChangeFunc(TiltBox *box);
bool myTiltSensorIsActiveFunc(TiltBox *box);
void myTransmitTiltStateFunc(TiltBox *box, unsigned char boxState);
void myWriteVisibleColorFunc(TiltBox *box, unsigned char r, unsigned char g, unsigned char b);

boolean wasTilted = false;

void setup() {
  Serial.begin(9600);

  // Initialize pins
  pinMode(axisPinN, INPUT_PULLUP);
  pinMode(axisPinS, INPUT_PULLUP);
  pinMode(axisPinE, INPUT_PULLUP);
  pinMode(axisPinW, INPUT_PULLUP);

  // Initialize RF library
  initRadio();

  // Initialize tilt_light_box library
  setSleepMillisFunc(mySleepFunc);
  setRandomValueFunc(myRandomValueFunc);
  setCurrentMillisFunc(myCurrentMillisFunc);
  setReceiveThemeChangeFunc(myReceiveThemeChangeFunc);
  setTileSensorIsActiveFunc(myTiltSensorIsActiveFunc);
  setTransmitTiltStateFunc(myTransmitTiltStateFunc);
  setWriteVisibleColorFunc(myWriteVisibleColorFunc);
  box = createTiltBox();
}

void loop() {
  runCycle(box);
}

void initRadio() {
  radio.begin();
  
  // The following settings match our node.js "nrf" usage settings
  radio.setChannel(0x4c);
  radio.setDataRate(RF24_1MBPS);
  radio.setCRCLength(RF24_CRC_16);
  radio.setRetries(15,15);
  
  radio.enableDynamicPayloads();
  // Disabled auto-ack in order to prevent overwhelming of server broadcast
  // NOTE: We never actually verified this was a problem once we removed
  // our explicit ack messages, but things seem stable now.. so no need to change.
  radio.setAutoAck(false);
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1, pipes[1]);
  radio.startListening();

  FastLED.addLeds<LPD8806, 5, 6, BRG>(leds, NUM_LEDS); 

  // This was blocking execution on my Uno for some reason
  //radio.printDetails();
}

uint8_t readThemeChangeFromRF() {
  // Read theme request from RF
  uint8_t rx_data[1] = {COLOR_ALG__NOOP};
  uint8_t len = 0;
  if (radio.available()) {
    boolean done;
    while (radio.available()) {
      len = radio.getDynamicPayloadSize();
      if (!len) {
        break;
      }
      radio.read( &rx_data, sizeof(rx_data) );
      // TODO [rkenney]: Remove debug
      Serial.print("Recieved theme change: ");
      Serial.print(rx_data[0]);
      Serial.print("\n");
    }
    // Send ACK
    // NOTE: Disabled ack in order to prevent overwhelming of server broadcast
    /*
    radio.stopListening();
    radio.write( &rx_data, sizeof(rx_data) );
    Serial.println("Sent response.");
    radio.startListening();
    */
  }
  return rx_data[0];
}

void mySleepFunc(unsigned long millis) {
  delay(millis);
}

int myRandomValueFunc(int min, int max) {
  return random(min, max);
}

unsigned long myCurrentMillisFunc() {
  return millis();
}

void myTransmitTiltStateFunc(TiltBox *box, unsigned char boxState) {
    radio.stopListening();
    uint8_t rx_data[1] = {BOX_STATE__TILTING};
    radio.write( &rx_data, sizeof(rx_data) );
    Serial.println("Sent tilt.");
    radio.startListening();
}

unsigned char myReceiveThemeChangeFunc(TiltBox *box)  {
  // Read theme request from RF
  uint8_t rx_data[1] = {COLOR_ALG__NOOP};
  while (radio.available()) {
    int len = radio.getDynamicPayloadSize();
    if (len < 1) {
      break;
    }
    radio.read( &rx_data, sizeof(rx_data) );
    Serial.print("Recieved theme change: ");
    Serial.print(rx_data[0]);
    Serial.print("\n");
    // Send ACK
    // NOTE: Disabled ack in order to prevent overwhelming of server broadcast
    /*
    radio.stopListening();
    radio.write( &rx_data, sizeof(rx_data) );
    Serial.println("Sent response.");
    radio.startListening();
    */
  }
  return rx_data[0];
}

void myWriteVisibleColorFunc(TiltBox *box, unsigned char r, unsigned char g, unsigned char b) {
  int i;
  for (i=0; i<NUM_LEDS; i++) {
    leds[i] = CRGB(r,g,b);
  }
  FastLED.show();
}

bool myTiltSensorIsActiveFunc(TiltBox *box) {
  bool isActive =
    pinIsActive(axisPinN) || 
    pinIsActive(axisPinS) || 
    pinIsActive(axisPinE) || 
    pinIsActive(axisPinW);
  return isActive;
}

bool pinIsActive(int pinNumber) {
  // NOTE: We invert the read value so we can make use of the
  // internal pull up resistors
  int pinValue = digitalRead(pinNumber);
  return (LOW == pinValue);
}

