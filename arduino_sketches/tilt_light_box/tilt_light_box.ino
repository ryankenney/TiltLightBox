#include <SPI.h>
#include <RF24.h>
#include <stdlib.h>
#include <tilt_light_box.h>

const int axisPinN = A1;
const int axisPinS = A2;
const int axisPinE = 8;
const int axisPinW = 7;
const int ledPinRed = 5;
const int ledPinGreen = 6;
const int ledPinBlue = 3;
const uint64_t pipes[2] = { 0xe7e7e7e7e7LL, 0xc2c2c2c2c2LL };
TiltBox* box;
const int RF_CE = 9;
const int RF_CSN = 10;
RF24 radio(RF_CE, RF_CSN);

uint8_t readThemeChangeFromRF();
void mySleepFunc(unsigned long millis);
int myRandomValueFunc(int min, int max);
unsigned long myCurrentMillisFunc();

void setup() {
  Serial.begin(9600);

  // Initialize pins
  pinMode(axisPinN, INPUT_PULLUP);
  pinMode(axisPinS, INPUT_PULLUP);
  pinMode(axisPinE, INPUT_PULLUP);
  pinMode(axisPinW, INPUT_PULLUP);
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinBlue, OUTPUT);

  // Initialize RF library
  radio.begin();
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1, pipes[0]);
  radio.startListening();
  radio.printDetails();

  // Initialize tilt_light_box library
  setSleepMillisFunc(mySleepFunc);
  setRandomValueFunc(myRandomValueFunc);
  setCurrentMillisFunc(myCurrentMillisFunc);
  box = createTiltBox();
  setBoxState(box, 0);
  setColorAlg(box, COLOR_ALG__PURPLE_CALM);
}

boolean wasTilted = false;

void loop() {  

  // Read theme request from RF
  uint8_t newTheme = readThemeChangeFromRF();

  // Apply any theme request
  if (newTheme != COLOR_ALG__NOOP) {
    setColorAlg(box, newTheme);
  }
  
  // Read tilt sensor
  boolean newlyTilting = false;
  boolean isTilted = (
    pinIsActive(axisPinN) || 
    pinIsActive(axisPinS) || 
    pinIsActive(axisPinE) || 
    pinIsActive(axisPinW));
  if (isTilted & !wasTilted) {
    newlyTilting = true;
  }

  // Apply change in tilt state to color algorithm
  if (newlyTilting) {
    setBoxState(box, BOX_STATE__TILTING);
  } else if (isTilted & !wasTilted) {
    // Do nothing. The lib rolls the color alg from __TILTING to __TILTED automatically
    // setColorAlg(box, BOX_STATE__TILTED);
  } else if (!isTilted & wasTilted) {
    setBoxState(box, BOX_STATE__UPRIGHT);
  }
  wasTilted = isTilted;
  
  // Read next color
  unsigned char color[3] = {0,0,0};
  getColor(box, color);

  // Write new color
  analogWrite(ledPinRed, color[0]);
  analogWrite(ledPinGreen, color[1]);
  analogWrite(ledPinBlue, color[2]);

  // Print debug
  /*
  Serial.print("RGB - ");
  Serial.print(color[0]);
  Serial.print(":");
  Serial.print(color[1]);
  Serial.print(":");
  Serial.print(color[2]);
  Serial.print("\n");
  delay(1000);
  */

}

uint8_t readThemeChangeFromRF() {
  // Read theme request from RF
  uint8_t rx_data[3] = {COLOR_ALG__NOOP};
  if (radio.available()) {
    boolean done;
    while (!done) {
      done = radio.read( &rx_data, sizeof(rx_data) );
      // TODO [rkenney]: Remove debug
      Serial.print("Recieved theme change: ");
      Serial.print(rx_data[0]);
      Serial.print("\n");
    }
    // Send ACK
    radio.stopListening();
    radio.write( &rx_data, sizeof(rx_data) );
    Serial.println("Sent response.");
    radio.startListening();
  } else {
    // TODO [rkenney]: Remove debug
    /*
    Serial.print("No messages.\n");
    delay(1000);
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

bool pinIsActive(int pinNumber) {
  // NOTE: We invert the read value so we can make use of the
  // internal pull up resistors
  int pinValue = digitalRead(pinNumber);
  return (LOW == pinValue);
}

