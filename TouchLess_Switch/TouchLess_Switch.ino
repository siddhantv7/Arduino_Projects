
const int RELAY = 3;
const int soundSensor = 2;
const int REDLED = 4;
const int GREENLED = 5;

bool LED_STATE = false;
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600); // Initialize serial communication for debugging
  pinMode(RELAY, OUTPUT);
  pinMode(soundSensor, INPUT); // Set the sensor pin as an input
  pinMode(REDLED, OUTPUT);
  pinMode(GREENLED, OUTPUT);
  digitalWrite(RELAY, LOW);
  digitalWrite(GREENLED, LOW);
  digitalWrite(REDLED, HIGH);
}

void loop() {
  int sensorValue = digitalRead(soundSensor);
  Serial.println(sensorValue);
  if ( LED_STATE == false) {
    if (sensorValue == LOW) {
      Serial.println("LED OFF!"); // Print a message when an obstacle is detected
      LED_STATE = true;
      digitalWrite(RELAY, HIGH);
      digitalWrite(GREENLED, LOW);
      digitalWrite(REDLED, HIGH);
      delay(70);
    }
  } else if (LED_STATE = true) {
    if (sensorValue == LOW) {
      Serial.println("LED ON!"); // Print a message when no obstacle is detected
      LED_STATE = false;
      digitalWrite(RELAY, LOW);
      digitalWrite(GREENLED, HIGH);
      digitalWrite(REDLED, LOW);
      delay(70);
    }
  }
  // put your main code here, to run repeatedly:
  delay(3);
}
