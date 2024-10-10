#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME "Irrigation system"
#define BLYNK_AUTH_TOKEN ""

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[ ] = "";

char ssid[ ] = "wifiname";
char pass[ ] = "wifiPassword";

BLYNK_WRITE(V0)  // function for switching off and on LED
{
  int value = (int)param.asInt();
  if (value == 1) {
    digitalWrite(D5, HIGH);
  }
  else {
    digitalWrite(D5, LOW);
  }
  Serial.print("V0 Slider value is: ");
  Serial.println(value);

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(D5, OUTPUT);
  Blynk.begin(auth, ssid, pass);

}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
}
