#define BLYNK_TEMPLATE_ID "TMPL3_2AgieTb"
#define BLYNK_TEMPLATE_NAME "petfeeder"
#define BLYNK_AUTH_TOKEN "qtOepag83rA7crC2oGCY-Ujw7C1UFdoH"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
char auth[ ] = "qtOepag83rA7crC2oGCY-Ujw7C1UFdoH";

// Your WiFi credentials.
// Set password to "" for open networks.

char ssid[ ] = "petfeeder";
char pass[ ] = "87654321";
int trigPin = D7;    // Trigger
int echoPin = D8;    // Echo
long duration, cm;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "in.pool.ntp.org");
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define IR D5
#define SERVO_MOTOR D6
String feedTime;

Servo myservo;  // create servo object to control a servo
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


BlynkTimer timer;

BLYNK_WRITE(V0)  // function for switching off and on LED
{

  int value = (int)param.asInt();

//  if (value == 1){
//    Blynk.logEvent("led_notification","LED ON h");
//  }
  
  Serial.print("V0 Slider value is: ");
  Serial.println(value);
  timeClient.update();
  if(value == 1){
      display.clearDisplay();
      display.setCursor(20, 20);
      display.println(timeClient.getFormattedTime());
      feedTime = timeClient.getFormattedTime();
      display.display(); 
      
      Blynk.virtualWrite(V1, feedTime);
      
      myservo.write(100);              // tell servo to go to position in variable 'pos'
      delay(2000);                       // waits 15ms for the servo to reach the position
      Serial.println("Motor start");
      myservo.write(0);              // tell servo to go to position in variable 'pos'
      delay(2000);
      Serial.println("Motor OFF");
  }

  
}

void sendsensor(){
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  float cloudValue = 9-cm;
  Serial.print(cm);
  Serial.println("cm");
  Blynk.virtualWrite(V2, cloudValue*10);

  if (cloudValue <= 2){
    Blynk.logEvent("empty_pet_feeder","Please fill the per feeder with some food. ");
  }
  }


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(SERVO_MOTOR);  // attaches the servo on GIO2 to the servo object
  myservo.write(100); 
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("Waiting...");

//Initialize a NTPClient to get time
        timeClient.begin();
        timeClient.setTimeOffset(19800);
  
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendsensor);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Get a time structure 
    timeClient.update();
    time_t epochTime = timeClient.getEpochTime();
    // Serial.print("Epoch Time: ");
    // Serial.println(epochTime);
    
    String formattedTime = timeClient.getFormattedTime();
    Serial.print("\nFormatted Time: ");
    Serial.println(formattedTime);
    
    int currentHour = timeClient.getHours();
    // Serial.print("Hour: ");
    // Serial.println(currentHour); 
    
    struct tm *ptm = gmtime ((time_t *)&epochTime); 

//Display time and servo motor working complete date:
  String currentDate = String(ptm->tm_year+1900) + "-" + String(ptm->tm_mon+1) + "-" + String(ptm->tm_mday);
  // Serial.print("Current date: ");
  // Serial.println(currentDate);
  
  int ir_value = digitalRead(IR);
  
  
  
  Serial.print("\nIR Value: ");
  Serial.println(ir_value);
  

  if((ir_value == 0)||((formattedTime == "06:00:00") || (formattedTime == "00:00:00"))){
      display.clearDisplay();
      display.setCursor(20, 5);
      display.println(formattedTime);
      feedTime = formattedTime;
      display.display(); 
      
      Blynk.virtualWrite(V1, feedTime);
      
      myservo.write(100);              // tell servo to go to position in variable 'pos'
      delay(2000);                       // waits 15ms for the servo to reach the position
      Serial.println("Motor start");
      myservo.write(0);              // tell servo to go to position in variable 'pos'
      delay(2000);
      Serial.println("Motor OFF");
  }
  

  
Serial.print("\n ----------------");
  Blynk.run();
  timer.run();
  delay(1000);
}
