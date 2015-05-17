// Color Demo

const int ledPinRed = 9;
const int ledPinGreen = 10;
const int ledPinBlue = 11;

void setup() {

  Serial.begin(9600);

  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinBlue, OUTPUT);
}

static int DELAY_MILLIS = 1;
static int COLOR_INCREMENT = 4;

int colorToShift = 0;
int colors[] = {0,0,0};
int direction = 1;

boolean colorIsComplete() {
  int nextValue = colors[colorToShift]+(COLOR_INCREMENT*direction);
  if (nextValue > 255 || nextValue < 0) {
    return true;
  }
  return false;
}

boolean directionIsComplete() {
  return (colorToShift >= 2 && colorIsComplete());
}

void selectNextColor() {
  colorToShift += 1;
}

void selectNextDirection() {
  colorToShift = 0;
  direction *= -1;
  if (direction < 0) {
    colors[0] = 255;
    colors[1] = 255;
    colors[2] = 255;
  } else {
    colors[0] = 0;
    colors[1] = 0;
    colors[2] = 0;
  }
}

void incrementColor() {
  colors[colorToShift] += (COLOR_INCREMENT*direction);
}

void writeColor(int r, int g, int b) {
  Serial.print("[");
  Serial.print(r);
  Serial.print(":");
  Serial.print(g);
  Serial.print(":");
  Serial.print(b);
  Serial.print("]");
  Serial.print(" ");
  Serial.println();
  analogWrite(ledPinRed, r);
  analogWrite(ledPinGreen, g);
  analogWrite(ledPinBlue, b);
}

void loop(){
  if (directionIsComplete()) {
    selectNextDirection();
  } else if (colorIsComplete()) {
    selectNextColor();
  }
  incrementColor();
  writeColor(colors[0], colors[1], colors[2]);
  delay(DELAY_MILLIS);
}


