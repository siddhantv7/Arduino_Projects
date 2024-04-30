#define BLYNK_TEMPLATE_ID "TMPL3Z6XntECk"
#define BLYNK_TEMPLATE_NAME "Smart Dustbin"
#define BLYNK_AUTH_TOKEN "lN5qY9WuQnzPECbXoy8thrVCZmdJK-7p"
String apiKey = "HGP3M3HKZC0USIMU";     //  Enter your Write API key from ThingSpeak
const char *server = "api.thingspeak.com";

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

char auth[ ] = "lN5qY9WuQnzPECbXoy8thrVCZmdJK-7p";
char ssid[ ] = "vishwakarma";
char pass[ ] = "8551806885";

BlynkTimer timer;
WiFiClient client;

#define IR D4          //pin where the dht11 is connected
#define RED_LED D2     // RED Led pin
#define GREEN_LED D1    // RED Led pin 
Servo s1;
const int trigPin = D5;
const int echoPin = D6;
// defines variables
long duration;
int distance;

void sendSensorData() {

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  Serial.print("Depth: ");
  Serial.println(distance);
  float deapth =  100 - (distance * 10);

  if (client.connect(server, 80))  //   "184.106.153.149" or api.thingspeak.com
  {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(deapth);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
  }
  else{Serial.print("error");}
  client.stop();




  Blynk.virtualWrite(V0, deapth);

  if (distance <= 2) {
    Blynk.logEvent("dustbin_full", "Please empty the Distbin No. 1. ");
  }

  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  if (distance < 3 )
  {
    digitalWrite(GREEN_LED, LOW);
    delay(1);
    digitalWrite(RED_LED, HIGH);

  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(IR, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  s1.attach(D3);

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendSensorData);
}

void loop() {
  // put your main code here, to run repeatedly:
  float ir = digitalRead(IR);
  Serial.print("IR Value: ");
  Serial.println(ir);

  if (ir == 0) {
    s1.write(180);
    delay(5000);
    s1.write(0);
    delay(1000);
  }
  Blynk.run();
  timer.run();
  delay(15000);
}
