#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME "Smart Dustbin"
#define BLYNK_AUTH_TOKEN ""

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h> // servo library  

Servo s1;
#define pirPin D1
#define servoPin D2
#define trigPin D3
#define echoPin D4
#define redLed D5
#define greenLed D6
#define SOUND_VELOCITY 0.034

int pirValue;
long duration;
float distanceCm;
BlynkTimer timer;

char auth[ ] = "kYybxZbitMDsANBsp-JXWvIA_2cDqqRZ";
char ssid[ ] = "dustbin";
char pass[ ] = "dustbin@123";

void setup()
{
  Serial.begin(115200);
  pinMode(pirPin, INPUT);
  s1.attach(servoPin);  // servo attach D3 pin of arduino
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(redLed, OUTPUT); // Sets the trigPin as an Output
  pinMode(greenLed, OUTPUT); // Sets the echoPin as an Input
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
  pirValue = digitalRead(pirPin);
  Serial.println(pirValue);
  if (pirValue == 0) {
    Serial.println("Motion detected");
    s1.write(170);
    delay(1000);
    s1.write(10);
    delay(5000);
    s1.write(170);
  }
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_VELOCITY / 2;
  Serial.print("Distance (cm): ");
  Serial.print(distanceCm);
  
  int percentCm = (distanceCm/24.8)*100; 
  Blynk.virtualWrite(V0, (100-percentCm)+6);
  

  if (distanceCm <= 4) {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    Serial.print("Red Led");
    Blynk.virtualWrite(V1, "Full");
    Blynk.logEvent("dustbin_full");
  }
  else if (distanceCm > 4) {
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, LOW);
    Serial.print("Green Led");
    Blynk.virtualWrite(V1, "Empty");
  }
}
