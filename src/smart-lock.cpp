#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_SSD1306.h> 
// Display libraries

#define SYSTEM_NAME "Smart Lock"
#define SYSTEM_VERSION "v1.1.0"
#define ButtonPin 4
#define LockPin 5

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 
// Width and height of display in pixels

#define OLED_RESET     -1
// Reset pina
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void version_display() {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(90, 56);
  display.print(SYSTEM_VERSION);
}

void locked_display() {
  display.clearDisplay();
  // Clear the buffer
  digitalWrite(LockPin, HIGH);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(47, 5);
  display.println("STATUS:");
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(29, 25);
  display.println("LOCKED");
  version_display();
  display.display();
  // Display text when the door is locked 
}

void setup() {
  Serial.begin(115200);
  Serial.println("=====================================");
  Serial.printf("%s v%s\n", SYSTEM_NAME, SYSTEM_VERSION);
  Serial.println("Developed by Maria Eduarda P. Jesus");
  Serial.println("=====================================");
    
  pinMode(ButtonPin, INPUT_PULLDOWN);
  pinMode(LockPin, OUTPUT);
  digitalWrite(LockPin, HIGH);
  
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  // Display init

  locked_display();
}

void loop() {
  int buttonState = digitalRead(ButtonPin);
  
  if (buttonState == HIGH) {
    digitalWrite(LockPin, LOW);
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(47, 5);
    display.println("STATUS:");
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(18, 25);
    display.println("UNLOCKED");
    version_display();
    display.display();
    // Display text when the door is open

    delay(5000);

    locked_display();
  } 
}

