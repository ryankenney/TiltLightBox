// Tilt Sensor LEDs

const int ledPin =  13;

const int axisPinX = 3;
const int axisPinY = 5;
const int axisPinZ = 6;

const int ledPinRed = 9;
const int ledPinGreen = 10;
const int ledPinBlue = 11;

void setup() {

  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);

  pinMode(axisPinX, INPUT);
  pinMode(axisPinY, INPUT);
  pinMode(axisPinZ, INPUT);

  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinBlue, OUTPUT);
}

int axisX = 0;
int axisY = 0;
int axisZ = 0;

void loop(){

  axisX = digitalRead(axisPinX);
  axisY = digitalRead(axisPinY);
  axisZ = digitalRead(axisPinX);

  int r = 0;
  int g = 0;
  int b = 0;

  if (axisX == HIGH) {
    r = 255;
  }
  if (axisY == HIGH) {
    g = 255;
  }
  if (axisZ == HIGH) {
    b = 255;
  }
  if (axisX == HIGH) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  setColor(r, g, b);

  delay(100);
}

void setColor(int r, int g, int b) {
    Serial.print("(");
    Serial.print(axisX);
    Serial.print(",");
    Serial.print(axisY);
    Serial.print(",");
    Serial.print(axisZ);
    Serial.print(") ");
    Serial.print(r);
    Serial.print(":");
    Serial.print(g);
    Serial.print(":");
    Serial.println(b);
    analogWrite(ledPinRed, r);
    analogWrite(ledPinGreen, g);
    analogWrite(ledPinBlue, b);
}

