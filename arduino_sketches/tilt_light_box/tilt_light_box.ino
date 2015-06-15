#include <stdlib.h>
#include <tilt_light_box.h>

TiltBox* box;

void mySleepFunc(unsigned long millis);
int myRandomValueFunc(int min, int max);
unsigned long myCurrentMillisFunc();

void setup() {
  // Initialize library
  setSleepMillisFunc(mySleepFunc);
  setRandomValueFunc(myRandomValueFunc);
  setCurrentMillisFunc(myCurrentMillisFunc);
  box = createTiltBox();
  Serial.begin(9600);
}

void loop() {
  unsigned char color[3] = {0,0,0};
  getColor(box, color);
  Serial.print("S");
  delay(1000);
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
