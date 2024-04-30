#include <Servo.h>
#include <ESP8266WiFi.h>
 
String apiKey = "HGP3M3HKZC0USIMU";     //  Enter your Write API key from ThingSpeak
 
const char *ssid =  "vishwakarma";     // replace with your wifi ssid and wpa2 key
const char *pass =  "8551806885";
const char *server = "api.thingspeak.com";

#define IR D4          //pin where the dht11 is connected
#define RED_LED D2     // RED Led pin
#define GREEN_LED D1    // RED Led pin 
Servo s1; 
const int trigPin = D5;
const int echoPin = D6;
// defines variables
long duration;
int distance;

WiFiClient client;

void setup() 
{
       Serial.begin(115200);
       pinMode(IR, INPUT);
       pinMode(RED_LED, OUTPUT);
       pinMode(GREEN_LED, OUTPUT);
       pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
       pinMode(echoPin, INPUT); // Sets the echoPin as an Input
       s1.attach(D3);
      
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
      
      
      float ir = digitalRead(IR);
      Serial.print("IR Value: ");
      Serial.print(ir);

      if (ir == 0){
         s1.write(180);  
         delay(5000);  
         s1.write(0);
         delay(1000);  
      }
      
      // Clears the trigPin
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      // Sets the trigPin on HIGH state for 10 micro seconds
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      // Reads the echoPin, returns the sound wave travel time in microseconds
      duration = pulseIn(echoPin, HIGH);
      // Calculating the distance
      distance = duration * 0.034 / 2;
      // Prints the distance on the Serial Monitor

      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(RED_LED, LOW);
              if (distance < 3 ) 
                 {
                     digitalWrite(GREEN_LED, LOW);
                     delay(1);
                     digitalWrite(RED_LED, HIGH);
                     
                 }
                 
              if (isnan(distance)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }
 
              if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                  {        
                     String postStr = apiKey;
                     postStr +="&field1=";
                     postStr += String(distance);
                     postStr += "\r\n\r\n";

                     client.print("POST /update HTTP/1.1\n");
                     client.print("Host: api.thingspeak.com\n");
                     client.print("Connection: close\n");
                     client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                     client.print("Content-Type: application/x-www-form-urlencoded\n");
                     client.print("Content-Length: ");
                     client.print(postStr.length());
                     client.print("\n\n");
                     client.print(postStr);

                     Serial.print("Distance: ");
                     Serial.println(distance);
                   }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);
}
