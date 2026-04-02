#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_SSD1306.h> 

#define SYSTEM_NAME "Smart Lock"
#define SYSTEM_VERSION "v2.0.0"
#define LockPin 5
#define BuzzerPin 18
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

void locked_display() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  display.println("DOOR LOCKED");
  display.setCursor(1, 20);
  display.println("DOOR LOCKED");
  display.setCursor(0, 30);
  display.println("Enter a password");
  version_display();
  display.display();
}
  
void setup() {
  Serial.begin(115200);
  Serial.println("=====================================");
  Serial.printf("%s v%s\n", SYSTEM_NAME, SYSTEM_VERSION);
  Serial.println("Developed by Maria Eduarda P. Jesus");
  Serial.println("=====================================");
  
  pinMode(LockPin, OUTPUT);
  digitalWrite(LockPin, HIGH);
  pinMode(BuzzerPin, OUTPUT);
  digitalWrite(BuzzerPin, HIGH);


  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  locked_display();
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    // Waits for the user to enter the password

    if (input == "0000") {
      digitalWrite(LockPin, LOW);

      digitalWrite(BuzzerPin, LOW);
      delay(300);
      digitalWrite(BuzzerPin, HIGH);
      
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 20);
      display.println("DOOR UNLOCKED");
      display.setCursor(1, 20);
      display.println("DOOR UNLOCKED");
      display.setCursor(0, 30);
      display.println("Closes in 5 seconds");
      version_display();
      display.display();
      // If the password is correct, the door opens
    
      delay(5000);
      digitalWrite(BuzzerPin, LOW);
      delay(200);
      digitalWrite(BuzzerPin, HIGH);
      locked_display();
      // Lock the door and start the loop again
    } 
    else {
      digitalWrite(BuzzerPin, LOW);
      delay(50);
      digitalWrite(BuzzerPin, HIGH);
      delay(50);
      digitalWrite(BuzzerPin, LOW);
      delay(50);
      digitalWrite(BuzzerPin, HIGH);
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 26);
      display.println("INCORRECT PASSWORD");
      display.setCursor(1, 26);
      display.println("INCORRECT PASSWORD");
      version_display();
      display.display();
      delay(1000);
      locked_display();
      // If the password is incorrect, it emits a different beep and restarts the loop
    }
  }
}


