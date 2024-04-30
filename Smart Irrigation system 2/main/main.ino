#define BLYNK_TEMPLATE_ID "TMPL3Fkpn5h_x"
#define BLYNK_TEMPLATE_NAME "tp"
#define BLYNK_AUTH_TOKEN "J_0PM2d8SqzxCVP2YEqsBWq3Xz_xR82e"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#define DHTPIN D6
#define DHTTYPE DHT11     // DHT 11


char auth[ ] = "J_0PM2d8SqzxCVP2YEqsBWq3Xz_xR82e";
char ssid[ ] = "irrigation";
char pass[ ] = "pass@123";

long moistureSensor = A0;
int relay = D5;
bool relayStatus = false;

DHT dht(DHTPIN, DHTTYPE);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(relay, OUTPUT);
  pinMode(moistureSensor, INPUT);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();

//
//  float h = dht.readHumidity();
//  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
//  int moistureValue =  analogRead(moistureSensor);
//  moistureValue = map(moistureValue, 0, 1023, 100, 0);
//  
//  Serial.println("Moisture: ");
//  Serial.println(moistureValue);
//  Serial.println("Humidity: ");
//  Serial.println(h);
//  Serial.println("Temperature: ");
//  Serial.println(t);
//  
//  Blynk.virtualWrite(V1, t - 2);
//  Blynk.virtualWrite(V2, h);
//  Blynk.virtualWrite(V3, moistureValue);
//}


}
