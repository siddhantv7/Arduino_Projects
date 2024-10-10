#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME "LED"
#define BLYNK_AUTH_TOKEN ""

#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp32.h>

char auth[ ] = "";

char ssid[ ] = "fire";
char pass[ ] = "fire@123";

BLYNK_WRITE(V0)  // function for switching off and on LED
{
  int value = (int)param.asInt();
  if (value == 1) {
    digitalWrite(4, HIGH);
  }
  else {
    digitalWrite(4, LOW);
  }
  Serial.print("V0 Slider value is: ");
  Serial.println(value);

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(4, OUTPUT);
  Blynk.begin(auth, ssid, pass);

}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
}
