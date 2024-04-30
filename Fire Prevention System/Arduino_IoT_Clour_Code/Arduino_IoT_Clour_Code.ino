#include <DHT.h>

#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);

// Pin Declaration 
int redLed = D1;
int greenLed = D2;
int buzzer = D3;
int smokeA0 = A0;
int flame_sensor = D4;
#define DHTPIN D5     


//Variables Declaration
int sensorThres = 400;      // Your threshold value
int flame_detected;   //Stores flame state
int analogSensor;   //Stores smoke value
float hum;   //Stores humidity value
float temp;   //Stores temperature value

void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  pinMode(flame_sensor, INPUT);
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, HIGH);
  dht.begin();

}

void loop() 
{
  // Display Smoke Level
  Serial.print("Smoke Level: ");
  Serial.print(analogSensor);
  Serial.println("ppm");

  // Display Fire State
  Serial.print("Flame State: ");
  Serial.println(flame_detected);

  // Display Humidity and Temperature
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print(" %, Temp: ");
  Serial.print(temp);
  Serial.println(" Celsius");
  // Send Humiditya and temperature to cloud

  if (analogSensor > sensorThres)
  {
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
      tone(buzzer, 5000, 400); // tone(buzzerPin, 5000, 400);

      delay(1000);
    // Send MSG smoke is detected
  }
  else if (flame_detected && (analogSensor > sensorThres))
  {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    noTone(buzzer);
    // Send MSG fire is detected
  }
  delay(1000);
}
