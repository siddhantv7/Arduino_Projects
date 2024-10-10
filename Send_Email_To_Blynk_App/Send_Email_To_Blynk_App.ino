#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME "Control LED"
#define BLYNK_AUTH_TOKEN ""

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>

char auth[ ] = "qILU_XEhhSYGogCYrY597CpfUJZQERcr";

// Your WiFi credentials.
// Set password to "" for open networks.

char ssid[ ] = "wifiname";
char pass[ ] = "";

BlynkTimer timer;

BLYNK_WRITE(V0)  // function for switching off and on LED
{
  int value = (int)param.asInt();

  if (value == 1){
    Blynk.logEvent("led_notification","LED ON h");
  }
  Serial.print("V0 Slider value is: ");
  Serial.println(value);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
//  timer.setInterval(1000L, controlLED);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
}
