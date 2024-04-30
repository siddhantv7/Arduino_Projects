//Tech Trends Shameer
//Control LED Using Blynk 2.0/Blynk IOT

#define BLYNK_TEMPLATE_ID "TMPL3E64pJ4X1"
#define BLYNK_TEMPLATE_NAME "Contorl LED"
#define BLYNK_AUTH_TOKEN "NK_8tVBdss7ieoZmBUGz8L73PT7Cu3R_"


#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>  
#include <BlynkSimpleEsp8266.h>
 

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "vishwakarma";  // Enter your Wifi Username
char pass[] = "";  // Enter your Wifi password

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
