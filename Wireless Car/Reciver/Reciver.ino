/*
  Arduino Wireless Communication Tutorial
        Example 1 - Receiver Code

  by Dejan Nedelkovski, www.HowToMechatronics.com

  Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>



//Motor 1 pins
int ENB = 9;
int in1 = 3;
int in2 = 4;

//Motor 2 pins
int ENA = 10;
int in3 = 5;
int in4 = 6;

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
struct data {
  int xAxis;
  int yAxis;

};
data receive_data;

//change below 2 line
unsigned long lastRadioCheckTime = 0;
const unsigned long radioCheckInterval = 500; // Check radio availability every 5 seconds



void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

}

void loop() {
  unsigned long currentMillis = millis();  //added line


  if (currentMillis - lastRadioCheckTime >= radioCheckInterval) {
    lastRadioCheckTime = currentMillis;

    if (!radio.available()) {
      //      Serial.println("Radio Not Available");
      // Reset radio module
      radio.begin();
      radio.openReadingPipe(0, address);
      radio.setPALevel(RF24_PA_MIN);
      radio.startListening();
    }
  }
  if (radio.available()) {
    radio.read(&receive_data, sizeof(data));
    Serial.print(receive_data.xAxis);
    Serial.print(receive_data.yAxis);

    if (receive_data.yAxis < 300) {
      //correct
      // Handle backward movement
      Serial.println("Backward");
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      analogWrite(ENA, 170);
      analogWrite(ENB, 170);
    }

    else if (receive_data.yAxis > 360) {
      // Handle forward movement
      Serial.println("Forward");
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      analogWrite(ENA, 170);
      analogWrite(ENB, 170);
    }
    else if (receive_data.xAxis < 300) {
      // Handle left movement
      Serial.println("Left");
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      analogWrite(ENA, 170);
      analogWrite(ENB, 170);
    }
    else if (receive_data.xAxis > 360) {
      // Handle Right movement
      Serial.println("Right");
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      analogWrite(ENA, 170);
      analogWrite(ENB, 170);
    }
    else {
      // Stop motors
      Serial.println("Stop");
      analogWrite(ENA, 0);
      analogWrite(ENB, 0);
    }

  }

}
