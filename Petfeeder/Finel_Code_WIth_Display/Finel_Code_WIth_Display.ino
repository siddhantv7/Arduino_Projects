
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Replace with your network credentials
const char *ssid     = "";
const char *password = "";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "in.pool.ntp.org");
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define IR D5
#define SERVO_MOTOR D6
bool on = false;

Servo myservo;  // create servo object to control a servo
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Servo Motor Setup
  myservo.attach(SERVO_MOTOR);  // attaches the servo on GIO2 to the servo object
  myservo.write(100); 


  //Display Setup
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("Waiting...");
  

  
  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

// Initialize a NTPClient to get time
  timeClient.begin();
  timeClient.setTimeOffset(19800);
}

void loop() {
  timeClient.update();

  time_t epochTime = timeClient.getEpochTime();
  Serial.print("Epoch Time: ");
  Serial.println(epochTime);
  
  String formattedTime = timeClient.getFormattedTime();
  Serial.print("Formatted Time: ");
  Serial.println(formattedTime);  

  int currentHour = timeClient.getHours();
  Serial.print("Hour: ");
  Serial.println(currentHour);  

  //Get a time structure
  struct tm *ptm = gmtime ((time_t *)&epochTime); 

  //Print complete date:
  String currentDate = String(ptm->tm_year+1900) + "-" + String(ptm->tm_mon+1) + "-" + String(ptm->tm_mday);
  Serial.print("Current date: ");
  Serial.println(currentDate);

  int ir_value = digitalRead(IR);
  Serial.println(ir_value);
  if((ir_value == 0)||((on == true)||((currentHour == 6) || (currentHour == 24)))){
      display.clearDisplay();
      display.setCursor(20, 20);
      display.println(timeClient.getFormattedTime());
      display.display(); 

      
      myservo.write(100);              // tell servo to go to position in variable 'pos'
      delay(2000);                       // waits 15ms for the servo to reach the position
      myservo.write(0);              // tell servo to go to position in variable 'pos'
      delay(2000);  
    }
  delay(1500);
}
