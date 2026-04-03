#include <WiFi.h>
#include <WebServer.h>
const char* ssid = ""; // Enter the network name
const char* password = ""; // Enter the network password
WebServer server(80);
//Wifi configuration

#define SYSTEM_NAME "Smart Lock"
#define SYSTEM_VERSION "v3.0.0"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_SSD1306.h> 

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
  display.setCursor(0, 16);
  display.println("Door locked!");
  display.setCursor(1, 16);
  display.println("Door locked!");
  display.println("Enter a password at");
  display.println("IP address");
  display.println(WiFi.localIP());
  display.display();
  version_display();
  display.display();
}

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  // Try connecting to local WiFi

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 26);
  display.println("Waiting for ");
  while (WiFi.status() != WL_CONNECTED){//Wait for connection
  }
  display.println("WiFi connection");
  display.display();
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 26);
  display.println("WiFi connected");
  display.display();
  // Communicates with display while WiFi is attempting to connect, and when it succeeds
}

void handleRoot() {
  //HTML code for mobile control website
  String html = "<html><head><meta name='viewport' content='width=device-width, initial-scale=1.0' charset='UTF-8'>";
  html += "<style>";
  html += "body { font-family: sans-serif; text-align: center; background-color: #f4f4f4; padding-top: 50px; }";
  html += ".keypad { display: grid; grid-template-columns: repeat(3, 80px); gap: 15px; justify-content: center; margin: 20px auto; }";
  html += "button { width: 80px; height: 80px; font-size: 28px; border-radius: 50%; border: none; background: #333; color: white; cursor: pointer; transition: 0.2s; }";
  html += "button:active { background: #666; transform: scale(0.95); }";
  html += ".display-input { font-size: 40px; letter-spacing: 15px; margin-bottom: 30px; height: 50px; color: #222; font-weight: bold; }";
  html += ".btn-send { grid-column: span 3; width: 270px; background: #28a745; height: 65px; border-radius: 10px; margin-top: 10px; font-weight: bold; color: white; }";
  html += ".btn-clear { background: #dc3545; }";
  html += "</style></head><body>";
  
  html += "<h1>Smart Lock</h1>";
  html += "<div class='display-input' id='dots'>____</div>";
  
  html += "<form id='lockForm' action='/login' method='POST'>";
  html += "<input type='hidden' name='password' id='passInput'>";
  
  html += "<div class='keypad'>";
  
  for(int i=1; i<=9; i++) {
    html += "<button type='button' onclick='addNumber(\"" + String(i) + "\")'>" + String(i) + "</button>";
  }
  
  html += "<button type='button' class='btn-clear' onclick='clearPass()'>C</button>";
  html += "<button type='button' onclick='addNumber(\"0\")'>0</button>";
  html += "<span></span>"; 
  html += "<button type='submit' class='btn-send'>OPEN THE DOOR</button>";
  html += "</div></form>";
  html += "<script>";
  html += "let pass = '';"; 
  html += "function addNumber(num) {";
  html += "  if(pass.length < 4) { pass += num; updateDisplay(); }";
  html += "}";
  html += "function clearPass() { pass = ''; updateDisplay(); }";
  html += "function updateDisplay() {";
  html += "  document.getElementById('passInput').value = pass;";
  html += "  let visual = '*'.repeat(pass.length) + '_'.repeat(4 - pass.length);";
  html += "  document.getElementById('dots').innerText = visual;";
  html += "}";
  html += "</script></body></html>";

  server.send(200, "text/html", html);
} // Sends the website to the mobile phone


void handleLogin(){
  String input = server.arg("password"); // Captures what was typed into the password field on the website

  if (input == "0000") {
      server.send(200, "text/html", "<h1>Abrindo...</h1><script>setTimeout(function(){window.location.href='/';}, 5000);</script>");
      digitalWrite(LockPin, LOW);

      digitalWrite(BuzzerPin, LOW);
      delay(300);
      digitalWrite(BuzzerPin, HIGH);
      
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0, 26);
      display.println("Door unlocked!");
      display.display();
    
      delay(5000);
      digitalWrite(BuzzerPin, LOW);
      delay(200);
      digitalWrite(BuzzerPin, HIGH);
      locked_display();
  } 
    else {
      server.send(200, "text/html", "<h1>Incorrect password.</h1><script>setTimeout(function(){window.location.href='/';}, 5000);</script>");
      digitalWrite(BuzzerPin, LOW);
      delay(50);
      digitalWrite(BuzzerPin, HIGH);
      delay(50);
      digitalWrite(BuzzerPin, LOW);
      delay(50);
      digitalWrite(BuzzerPin, HIGH);
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0, 16);
      display.println("Incorrect");
      display.println("password!");
      display.display();
      delay(1000);
      locked_display();
    }
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

  initWiFi();
  delay(1000);
  // Runs the WiFi connection void and waits 1 second to continue after WiFi is connected

  server.on("/", handleRoot); // If the user accesses the raw IP address, the handleRoot is called
  server.on("/login", handleLogin); // Check password
  server.begin();             // Start the server

  locked_display();
}

void loop() {
  server.handleClient(); // Monitors whether anyone has accessed the website
}



