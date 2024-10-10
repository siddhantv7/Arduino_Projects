#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME "Health Monitor"
#define BLYNK_AUTH_TOKEN "-"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[ ] = "R3X_Cx_TRQnRVTOxoF03-O_HqvOxhoy1";
char ssid[ ] = "Health";
char pass[ ] = "Health123";

long analogSensor = A0;
int digitalSensor = D5;


void setup() {
  // put your setup code here, to run once:
  pinMode(digitalSensor, INPUT);
  pinMode(analogSensor, INPUT);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
  // put your main code here, to run repeatedly:
  int pulseSensor =  analogRead(analogSensor);
  int tempSensor =  digitalRead(digitalSensor);

  Serial.print("Pulse: ");
  Serial.println(pulseSensor);
  Serial.print("Body Temperature: ");
  Serial.println(tempSensor);

  Blynk.virtualWrite(V0, pulseSensor);
  Blynk.virtualWrite(V1, tempSensor);
  delay(100);
}
