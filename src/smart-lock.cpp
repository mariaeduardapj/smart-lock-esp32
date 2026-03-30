const String SYSTEM_VERSION = "v1.1.0";

#include <Arduino.h>

#define ButtonPin 4
#define LockPin 5
// Identifies the microcontroller's inputs and outputs.

void setup() {
  Serial.begin(115200);
  Serial.println("Smart Lock desenvolved by Maria Eduarda P. Jesus");
  Serial.println(SYSTEM_VERSION);
    
  pinMode(ButtonPin, INPUT_PULLDOWN);
  pinMode(LockPin, OUTPUT);

  digitalWrite(LockPin, HIGH);
  // Causes the relay to start off (relay works in reverse).
}

void loop() {
int buttonState = digitalRead(ButtonPin);

if (buttonState == HIGH) {
  digitalWrite(LockPin, LOW);
  delay(5000);
  // Pressing the button activates the relay (open the door for 5s).
} else {
  digitalWrite(LockPin, HIGH);
}
}