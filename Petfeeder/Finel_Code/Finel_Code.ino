
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Servo.h>

// Replace with your network credentials
const char *ssid     = "wifiname";
const char *password = "wifipassword";

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "in.pool.ntp.org");
#define IR D1
#define SERVO_MOTOR D2
bool on = false;

Servo myservo;  // create servo object to control a servo

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  myservo.attach(SERVO_MOTOR);  // attaches the servo on GIO2 to the servo object
  myservo.write(0); 


  
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
      myservo.write(0);              // tell servo to go to position in variable 'pos'
      delay(2000);                       // waits 15ms for the servo to reach the position
      
      myservo.write(100);              // tell servo to go to position in variable 'pos'
      delay(2000);  
    }
  delay(2000);
}
