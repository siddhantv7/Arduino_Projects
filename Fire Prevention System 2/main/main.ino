#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""
#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// Pin Declaration
int redLed = 18;
int greenLed = 19;
int buzzer = 21;
int smokeSensor = 33;
int flameSensor = 27;
#define DHTPIN 26

//Variables Declaration
int sensorThres = 400;      // Your threshold value
int flame_detected;   //Stores flame state
int analogSensor;   //Stores smoke value
float humi;   //Stores humidity value
float temp;   //Stores temperature value

#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

char auth[ ] = "AXLwQ58im3kHo2De2PtzUmnmGF3m6XB5";
char ssid[ ] = "fire";
char pass[ ] = "fire@123";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeSensor, INPUT);
  pinMode(flameSensor, INPUT);
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  Blynk.begin(auth, ssid, pass);


}

void loop() {

  // put your main code here, to run repeatedly:
  Blynk.run();
  temp = dht.readTemperature();
  humi = dht.readHumidity();
  analogSensor = analogRead(smokeSensor);
  flame_detected = digitalRead(flameSensor);



  Serial.print("Humidity: ");
  Serial.print(humi);
  Serial.print(" %, Temp: ");
  Serial.print(temp-2);
  Serial.println(" Celsius");
  Serial.print("Smoke Level: ");
  Serial.print(analogSensor);
  Serial.println("ppm");
  Serial.print("Flame State: ");
  Serial.println(flame_detected);
  if(analogSensor >1500){
    Blynk.setProperty(V2, "color", "#D3435C");
    
    }

  if (!flame_detected) {
    Blynk.logEvent("fire_detected", "🔥 Fire Alert: Evacuate now. Use nearest exit. Stay calm. Safety first. 🔥");
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    digitalWrite(buzzer, HIGH);
    Blynk.virtualWrite(V4, "Fire Detected");
    Blynk.setProperty(V3, "color", "#D3435C");
    delay(2000);
  }
  else {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    digitalWrite(buzzer, LOW);
    Blynk.virtualWrite(V4, "You are safe!");
    Blynk.setProperty(V3, "color", "#008000");
  }
  Blynk.virtualWrite(V0, temp-2);
  Blynk.virtualWrite(V1, humi);
  Blynk.virtualWrite(V2, analogSensor);
  Blynk.virtualWrite(V3, flame_detected);
  Blynk.setProperty(V2, "color", "#008000");
}
