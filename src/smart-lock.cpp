#include <Arduino.h>

#define SYSTEM_NAME "Smart Lock"
#define SYSTEM_VERSION "v1.0.0"
#define ButtonPin 4
#define LockPin 5
// Identifies the microcontroller's inputs and outputs.

void setup() {
  Serial.begin(115200);
  Serial.println("=====================================");
  Serial.printf("%s %s\n", SYSTEM_NAME, SYSTEM_VERSION);
  Serial.println("Developed by Maria Eduarda P. Jesus");
  Serial.println("=====================================");
    
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
