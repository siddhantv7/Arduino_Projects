#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME "Send data"
#define BLYNK_AUTH_TOKEN ""

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[ ] = "";

// Your WiFi credentials.
// Set password to "" for open networks.

char ssid[ ] = "";
char pass[ ] = "";

int trigPin = D5;    // Trigger
int echoPin = D6;    // Echo
long duration, cm;

BlynkTimer timer;

// V1 LED Widget is blinking

BLYNK_WRITE(V1)  // function for switching off and on LED
{

  int value = (int)param.asInt();

  if (value == 1){
    digitalWrite(D3, HIGH);
  }
  else{
    digitalWrite(D3, LOW);
    }
  
  Serial.print("V0 Slider value is: ");
  Serial.println(value);
  
}

void blinkLedWidget()  // function for switching off and on LED
{

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
 
  Serial.println(cm);  
  Blynk.virtualWrite(V0, cm);
  
}

void setup()
{
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(D3, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, blinkLedWidget);
}

//In the loop function include Blynk.run() command.
void loop()
{
  Blynk.run();
  timer.run();
}
