// Tilt Sensor LEDs

const int axisPinN = A1;
const int axisPinS = A2;
const int axisPinE = 8;
const int axisPinW = 7;

const int ledPinRed = 3;
const int ledPinGreen = 5;
const int ledPinBlue = 6;

void setup() {

  Serial.begin(9600);

  pinMode(axisPinN, INPUT);
  pinMode(axisPinS, INPUT);
  pinMode(axisPinE, INPUT);
  pinMode(axisPinW, INPUT);

  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinBlue, OUTPUT);
}

int axisN = 0;
int axisS = 0;
int axisE = 0;
int axisW = 0;

void loop(){
  // read the state of the pushbutton value:
  axisN = digitalRead(axisPinN);
  axisS = digitalRead(axisPinS);
  axisE = digitalRead(axisPinE);
  axisW = digitalRead(axisPinW);


  if (axisN == HIGH) {
      writeState(axisN, axisS, axisE, axisW, 255, 0, 0);
  } else if (axisS == HIGH) {
      writeState(axisN, axisS, axisE, axisW, 0, 255, 0);
  } else if (axisE == HIGH) {
      writeState(axisN, axisS, axisE, axisW, 0, 0, 255);
  } else if (axisW == HIGH) {
      writeState(axisN, axisS, axisE, axisW, 255, 0, 255);
  } else {
      writeState(axisN, axisS, axisE, axisW, 255, 255, 255);
  }
  delay(100);
}


void writeState(int n, int s, int e, int w, int r, int g, int b) {
  Serial.print("[");
  Serial.print(r);
  Serial.print(":");
  Serial.print(g);
  Serial.print(":");
  Serial.print(b);
  Serial.print("]");
  Serial.print(" ");
  if (n == HIGH) {
    Serial.print("N");
  }
  if (s == HIGH) {
    Serial.print("S");
  }
  if (e == HIGH) {
    Serial.print("E");
  }
  if (w == HIGH) {
    Serial.print("W");
  }
  Serial.println();
  analogWrite(ledPinRed, r);
  analogWrite(ledPinGreen, g);
  analogWrite(ledPinBlue, b);
}

