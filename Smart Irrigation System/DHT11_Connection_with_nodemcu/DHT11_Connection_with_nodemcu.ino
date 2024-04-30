/*This code is written By Arduino projects*/
/*If you want to contact us the click on below link*/
//https://arduinosproject1.blogspot.com/p/contact-details.html

//Connection


#include <ESP8266WiFi.h>
#include "DHT.h"

String apiKey = "PNH6PZNMXCDSRHPW";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "visXXXXXXXXX";     // replace with your wifi ssid and wpa2 key
const char *pass =  "855XXXXXXXXXX";
const char* server = "api.thingspeak.com";

#define DHTPIN D3          //pin where the dht11 is connected
#define MOI A0        //pin where moisture snesor is connected
#define RELAY D2        //pin where relay is connecter

DHT dht(DHTPIN, DHT11);

WiFiClient client;

void setup()
{
  Serial.begin(115200);
  delay(10);
  dht.begin();

  pinMode (MOI,INPUT);
  pinMode (RELAY,OUTPUT);
  

  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

}

void loop()
{

  float h = dht.readHumidity();
  float t = dht.readTemperature();

 
  if (isnan(h) || isnan(t))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if (client.connect(server, 80))  //   "184.106.153.149" or api.thingspeak.com
  {

    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(t);
    postStr += "&field2=";
    postStr += String(h);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" degrees Celcius");
    Serial.print(" Humidity: ");
    Serial.print(h);
    Serial.println("%.");
  }
  client.stop();

  Serial.println("Waiting...");

  // thingspeak needs minimum 15 sec delay for updates
  delay(1000);
}
