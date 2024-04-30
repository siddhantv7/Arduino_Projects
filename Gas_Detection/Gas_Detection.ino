#define BLYNK_TEMPLATE_ID "TMPL3PG7TwiUg"
#define BLYNK_TEMPLATE_NAME "Gas Leakage Detection"
#define BLYNK_AUTH_TOKEN "UaozLusMAhgQdmR5qmLPXKkQEsy8B5P8"
#define BLYNK_PRINT Serial

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

char auth[] = BLYNK_AUTH_TOKEN;// Enter your Auth token
char ssid[] = "wifi_name";//Enter your WIFI SSIS
char pass[] = "password";//Enter your WIFI password

#define SENSOR_PIN A0
#define GREEN_LED D6
#define RED_LED D7
#define BUZZER_PIN D5


void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();  // Turn on the backlight
  lcd.clear();  // Clear the LCD screen
  
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  Blynk.begin(auth, ssid, pass);
  
  lcd.print("Starting Project");
  delay(1000);
  lcd.clear();  // Clear the LCD screen
}

void loop() {
  Blynk.run();
  lcd.clear();  // Clear the LCD screen
  int sensorValue = analogRead(SENSOR_PIN);
  int sensor = map(sensorValue, 0, 1024, 0, 100);
  Blynk.virtualWrite(V0, sensor);

  Serial.print("Smoke Value1: ");
  Serial.println(sensorValue);
  Serial.print("Smoke Value2: ");
  Serial.print(sensor);
  Serial.println("%");

  lcd.setCursor(0, 0);
  lcd.print("Gas Value: ");
  lcd.print(sensor);

  if (sensor <= 40) {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Status: Safe");
    Blynk.virtualWrite(V1, "You Are Safe");
  } else if (40 < sensor && sensor <= 60) {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Status: Detected");
    Blynk.virtualWrite(V1, "Gas Leakage Detected");
  } else if (sensor > 50) {
    Blynk.logEvent("gas_detected", "Gas detected! Please Check.");
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER_PIN, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Status: Danger");
    Blynk.virtualWrite(V1, "You Are In Danger");
  }else{
    digitalWrite(BUZZER_PIN, LOW);
    }
  
}
