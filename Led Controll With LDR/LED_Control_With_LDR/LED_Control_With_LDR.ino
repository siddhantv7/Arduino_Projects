#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME "Light"
#define BLYNK_AUTH_TOKEN ""

#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp32.h>

// Pin Declaration
const int RELAY = 19;
const int SENSORPIN = 21;
const int LED = 27;
bool buttonOn = false;
bool buttonOff = false;
bool LED_STATE = false;

char auth[ ] = BLYNK_AUTH_TOKEN;
char ssid[ ] = "light";
char pass[ ] = "password";



BLYNK_WRITE(V0)  // function for switching off and on LED
{
  int value = (int)param.asInt();

  if (value == 1) {
    digitalWrite(RELAY, LOW);
    digitalWrite(LED, HIGH);
    buttonOn = true;
    Serial.print("V0 Slider value is: ");
    Serial.println(value);
  }
  else {
    digitalWrite(RELAY, HIGH);
    digitalWrite(LED, LOW);
    buttonOn = false;
  }
  Serial.print("V0 Slider value is: ");
  Serial.println(value);

}


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600); // Initialize serial communication for debugging
  pinMode(RELAY, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(SENSORPIN, INPUT); // Set the sensor pin as an input
  digitalWrite(RELAY, LOW);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
  int sensorValue = digitalRead(SENSORPIN);
  Serial.println(sensorValue);
  if (buttonOn == false) {
    if ( LED_STATE == false) {
      LED_STATE = true;
      if (sensorValue == 1) {
        Serial.println("LED ON!"); // Print a message when an obstacle is detected
        digitalWrite(RELAY, LOW);
        digitalWrite(LED,   HIGH);
        //        Blynk.virtualWrite(V0, 1);
        delay(100);
      }
    } else if (LED_STATE = true) {
      LED_STATE = false;
      if (sensorValue == 0) {
        Serial.println("LED OFF!"); // Print a message when no obstacle is detected
        digitalWrite(RELAY, HIGH);
        digitalWrite(LED, LOW);
        //        Blynk.virtualWrite(V0, 0);
        delay(100);
      }
    }
  }
}
