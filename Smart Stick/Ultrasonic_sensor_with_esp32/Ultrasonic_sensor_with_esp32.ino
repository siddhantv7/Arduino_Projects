/*
   This ESP32 code is created by esp32io.com

   This ESP32 code is released in the public domain

   For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-ultrasonic-sensor
*/

#define TRIGPIN1 23
#define ECHOPIN1 22
#define TRIGPIN2 5
#define ECHOPIN2 4
#define TRIGPIN3 19
#define ECHOPIN3 18
#define BUZZERPIN 25
#define REDLEDPIN 26

float duration, distance1, distance2, distance3;

void setup() {
  // begin serial port
  Serial.begin (9600);

  pinMode(TRIGPIN1, OUTPUT); // Sets the TRIGPIN1 as an Output
  pinMode(ECHOPIN1, INPUT); // Sets the ECHOPIN1 as an Input
  pinMode(TRIGPIN2, OUTPUT); // Sets the TRIGPIN2 as an Output
  pinMode(ECHOPIN2, INPUT); // Sets the ECHOPIN2 as an Input
  pinMode(TRIGPIN3, OUTPUT); // Sets the TRIGPIN3 as an Output
  pinMode(ECHOPIN3, INPUT); // Sets the ECHOPIN3 as an Input

}

void loop() {

  //  -------------------------------------- UL1------------------------------------------
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIGPIN1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN1, LOW);

  // measure duration of pulse from ECHO pin
  duration = pulseIn(ECHOPIN1, HIGH);

  // calculate the distance
  distance1 = 0.017 * duration;

  // print the value to Serial Monitor
  Serial.print("Distance1: ");
  Serial.print(distance1);
  Serial.println(" cm");


  //  -------------------------------------- UL1------------------------------------------
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIGPIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN2, LOW);

  // measure duration of pulse from ECHO pin
  duration = pulseIn(ECHOPIN2, HIGH);

  // calculate the distance
  distance2 = 0.017 * duration;

  // print the value to Serial Monitor
  Serial.print("Distance2: ");
  Serial.print(distance2);
  Serial.println(" cm");

  //  -------------------------------------- UL1------------------------------------------
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIGPIN3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN3, LOW);

  // measure duration of pulse from ECHO pin
  duration = pulseIn(ECHOPIN3, HIGH);

  // calculate the distance
  distance3 = 0.017 * duration;

  // print the value to Serial Monitor
  Serial.print("Distance3: ");
  Serial.print(distance3);
  Serial.println(" cm");



  //  -------------------------------------- Buzzer and LED ------------------------------------------
  if (distance1 < 20 ) {
    digitalWrite(33, HIGH);
//    digitalWrite(REDLEDPIN, HIGH);
delay(500);
  }


  delay(500);
}
