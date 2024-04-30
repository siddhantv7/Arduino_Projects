
#include <ESP8266WiFi.h>

String apiKey = "2UXZXFQA1RFYO16R";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "vishwakarma";     // replace with your wifi ssid and wpa2 key
const char *pass =  "8551806885";
const char *server = "api.thingspeak.com";


#define MOI A0        //pin where moisture snesor is connected




WiFiClient client;

void setup()
{
  Serial.begin(115200);
  delay(10);
  pinMode (MOI,INPUT);

  

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

  float moisture_output = analogRead(MOI);

  if (isnan(moisture_output))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if (client.connect(server, 80))  //   "184.106.153.149" or api.thingspeak.com
  {

    String postStr = apiKey;
    postStr += "&field3=";
    postStr += String(moisture_output);
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

    Serial.print("Soil Moisture: ");
    Serial.print(moisture_output);
    Serial.println("%");
  }
  client.stop();

  Serial.println("Waiting...");

  // thingspeak needs minimum 15 sec delay for updates
  delay(1000);
}
