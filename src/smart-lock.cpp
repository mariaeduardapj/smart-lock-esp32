#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_SSD1306.h> 

#define SYSTEM_NAME "Smart Lock"
#define SYSTEM_VERSION "v1.2.0"
#define ButtonPin 4
#define LockPin 5

#define BuzzerPin 18
// Identify buzzer pin

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 
#define OLED_RESET     -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void version_display() {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(90, 56);
  display.print(SYSTEM_VERSION);
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

  pinMode(BuzzerPin, OUTPUT);
  digitalWrite(BuzzerPin, HIGH);
  // Set the buzzer as output and make it start off (works in reverse)
  
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display.clearDisplay();
}

void loop() {
  int buttonState = digitalRead(ButtonPin);
  
  if (buttonState == HIGH) {
    digitalWrite(LockPin, LOW);

    digitalWrite(BuzzerPin, LOW);
    delay(300);
    digitalWrite(BuzzerPin, HIGH);
    // When the door opens, the buzzer emits a sound for 0.3s
    
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
  
    delay(5000);

    digitalWrite(BuzzerPin, LOW);
    delay(200);
    digitalWrite(BuzzerPin, HIGH);
    // When the door closes, the buzzer emits a sound for 0,2s
  } 
  else {
    digitalWrite(LockPin, HIGH);
    display.clearDisplay();
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
  }
}

