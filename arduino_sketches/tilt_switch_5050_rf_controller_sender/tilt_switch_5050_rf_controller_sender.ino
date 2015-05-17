// RF Sender

#include <SPI.h>
#include <RF24.h>
 
#define LED 2
#define RF_CS 9
#define RF_CSN 10
RF24 radio(RF_CS, RF_CSN);
const uint64_t pipes[2] = { 0xe7e7e7e7e7LL, 0xc2c2c2c2c2LL };

const int axisPinN = A1;
const int axisPinS = A2;
const int axisPinE = 8;
const int axisPinW = 7;

int axisN = 0;
int axisS = 0;
int axisE = 0;
int axisW = 0;

uint8_t lastR = 0;
uint8_t lastG = 0;
uint8_t lastB = 0;

bool sentInitialState = false;
bool lastTransmitSucceed = false;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  radio.begin();
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1, pipes[1]);
  radio.startListening();
  radio.printDetails();

  pinMode(axisPinN, INPUT);
  pinMode(axisPinS, INPUT);
  pinMode(axisPinE, INPUT);
  pinMode(axisPinW, INPUT);

  // Invert pin's high/low state, and trigger use of internal pull-up resistor
  // (saves the need to add our own, external pull-down reistors)
  digitalWrite(axisPinN, HIGH);
  digitalWrite(axisPinS, HIGH);
  digitalWrite(axisPinE, HIGH);
  digitalWrite(axisPinW, HIGH);
}

/* Remove old
unsigned long packRGB(int r, int g, int b) {
  unsigned long color = 0;
  color |= a << 24;
  color |= r << 16;
  color |= g << 8;
  color |= b;
  return color;
}
*/

void loop() {

  uint8_t data[32];  // we'll transmit a 32 byte packet

  // read the state of the pushbutton value:
  axisN = digitalRead(axisPinN);
  axisS = digitalRead(axisPinS);
  axisE = digitalRead(axisPinE);
  axisW = digitalRead(axisPinW);
  if (axisN == LOW) {
    data[0] = 255;
    data[1] = 0;
    data[2] = 0;
  } else if (axisS == LOW) {
    data[0] = 0;
    data[1] = 255;
    data[2] = 0;
  } else if (axisE == LOW) {
    data[0] = 0;
    data[1] = 0;
    data[2] = 255;
  } else if (axisW == LOW) {
    data[0] = 255;
    data[1] = 0;
    data[2] = 255;
  } else {
    data[0] = 255;
    data[1] = 255;
    data[2] = 255;
  }
  if (sentInitialState && lastTransmitSucceed && data[0] == lastR && data[1] == lastG && data[2] == lastB) {
    return;
  }
  lastR = data[0];
  lastG = data[1];
  lastB = data[2];

  Serial.print("Sending color: ");
  Serial.print(data[0]);
  Serial.print(",");
  Serial.print(data[1]);
  Serial.print(",");
  Serial.print(data[2]);
  Serial.println("");

  unsigned long time = millis();
 
  // transmit the data
  radio.stopListening();
  radio.write( &data, sizeof(data) );
  radio.startListening();
  lastTransmitSucceed = false;

  // listen for acknowledgement from the receiver
  unsigned long started_waiting_at = millis();
  bool timeout = false;
  while (!radio.available() && ! timeout)
    if (millis() - started_waiting_at > 250 )
      timeout = true;
 
  if (timeout){
    Serial.println("Failed, response timed out.");
  } else {

    sentInitialState = true;
    lastTransmitSucceed = true;

    // the receiver is just going to spit the data back
    radio.read( &data, sizeof(data) );

    digitalWrite(LED, HIGH);
    delay(100);  // light up the LED for 100ms if it worked.
    digitalWrite(LED, LOW);

    Serial.print("Got response, round trip delay: ");
    Serial.print(millis() - started_waiting_at);
    Serial.println("");
  }

}

