

#define BLYNK_TEMPLATE_ID "TTMPL3xEcJkI2e"
#define BLYNK_TEMPLATE_NAME "Smart Irrigation System"
#define BLYNK_AUTH_TOKEN "B-ZjZaOMuDVknmG4B2wz3R3QrGYKbgG7"
#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
// Pin Declaration
#define rainSensor D1
#define moistureSensor A0
#define pirSensor D3
#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Variable Declarations
int rain;
int moisture;
float humidity;
float temperature;
int motion;

char auth[] = "B-ZjZaOMuDVknmG4B2wz3R3QrGYKbgG7";
char ssid[] = "Realme 20@";
char pass[] = "@dineshthakekarx";

void setup() {
  Serial.begin(9600);
  pinMode(rainSensor, INPUT);
  pinMode(moistureSensor, INPUT);
  pinMode(pirSensor, INPUT);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();

  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  moisture = analogRead(moistureSensor);
  int moistureValue = map(moisture, 0, 1023, 100, 0);
  int percentage = map(moistureValue, 0, 100, 0, 100);
  rain = digitalRead(rainSensor);
  motion = digitalRead(pirSensor);

  Serial.print("Humidity: ");
  Serial.println(humidity);
  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.print("Moisture1: ");
  Serial.println(percentage);
  Serial.print("Moisture2: ");
  Serial.println(moistureValue);
  Serial.print("Rain: ");
  Serial.println(rain);
  Serial.print("Motion: ");
  Serial.println(motion);

  Blynk.virtualWrite(V2, humidity);
  Blynk.virtualWrite(V3, temperature);
  Blynk.virtualWrite(V1, percentage);

  if (percentage < 30) {
    Blynk.logEvent("dry_soil", "The moisture in soil is very low!");
  }
  
  if (rain == 0) {
    Serial.println("Rain Detected");
    Blynk.virtualWrite(V0, "Rain Detected");
    Blynk.logEvent("raindetection", "It is raining in the farm ");
  } else {
    Serial.println("Rain Not Detected");
    Blynk.virtualWrite(V0, "Rain Not Detected");
  }
  
  if (motion) {
    Serial.print("Motion Detected");
    Blynk.virtualWrite(V4, "Motion Detected");
  } else {
    Serial.print("Motion Not Detected");
    Blynk.virtualWrite(V4, "Motion Not Detected");
  }
}
