#include <stdlib.h>
#include <tilt_light_box.h>

const int axisPinN = A1;
const int axisPinS = A2;
const int axisPinE = 8;
const int axisPinW = 7;
const int ledPinRed = 5;
const int ledPinGreen = 6;
const int ledPinBlue = 3;

TiltBox* box;

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

  // Initialize our library
  setSleepMillisFunc(mySleepFunc);
  setRandomValueFunc(myRandomValueFunc);
  setCurrentMillisFunc(myCurrentMillisFunc);
  box = createTiltBox();
  setBoxState(box, 0);
  setColorAlg(box, COLOR_ALG__PURPLE_CALM);
}

boolean wasTilted = false;

void loop() {

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

