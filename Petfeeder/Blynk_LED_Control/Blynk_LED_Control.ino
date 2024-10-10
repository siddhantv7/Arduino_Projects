//Tech Trends Shameer
//Control LED Using Blynk 2.0/Blynk IOT

#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME "Contorl LED"
#define BLYNK_AUTH_TOKEN ""


#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>  
#include <BlynkSimpleEsp8266.h>
 

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "wifiname";  // Enter your Wifi Username
char pass[] = "wifipassword";  // Enter your Wifi password

int ledpin = D4;
void setup()
{     
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);    
  pinMode(ledpin,OUTPUT);
}

void loop()
{
  Blynk.run(); 
}
