
#include <ESP8266WiFi.h>
#include "DHT.h"

String apiKey = "2UXZXFQA1RFYO16R";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "vishwakarma";     // replace with your wifi ssid and wpa2 key
const char *pass =  "8551806885";
const char *server = "api.thingspeak.com";

#define DHTPIN D3          //pin where the dht11 is connected
#define MOI A0        //pin where moisture snesor is connected
#define RELAY D5        //pin where relay is connecter

DHT dht(DHTPIN, DHT11);

WiFiClient client;

void setup()
{
  Serial.begin(115200);
  delay(10);
  dht.begin();

  pinMode (MOI,INPUT);
  pinMode (RELAY,OUTPUT);

//  Serial.println("Connecting to ");
//  Serial.println(ssid);
//
//  WiFi.begin(ssid, pass);
//
//  while (WiFi.status() != WL_CONNECTED)
//  {
//    delay(500);
//    Serial.print(".");
//  }
//  Serial.println("");
//  Serial.println("WiFi connected");

}

void loop()
{
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  float moisture_output = analogRead(MOI) / 1023.00;
  float moisture_percentage = ( 100.00 - (moisture_output) * 100.00 );

    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" degrees Celcius");
    Serial.print(" Humidity: ");
    Serial.print(h);
    Serial.println("%.");
    Serial.print("Soil Moisture: ");
    Serial.print(moisture_percentage);
    Serial.println("%");

  if(moisture_percentage < 40){
  digitalWrite(D5, LOW);
  delay(10000);
  digitalWrite(D5, HIGH);
  delay(5000);
    }

  // thingspeak needs minimum 15 sec delay for updates
  delay(1000);
}
