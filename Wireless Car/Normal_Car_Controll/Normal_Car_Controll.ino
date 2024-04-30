

//Motor 1 pins
int ENB = 9;
int in1 = 3;
int in2 = 4;

//Motor 2 pins
int ENA = 10;
int in3 = 5;
int in4 = 6;




void setup() {
  Serial.begin(9600);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);



}

void loop() {


  // Handle left movement
  Serial.println("backward");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
delay(5000);
  // Handle right movement
  Serial.println("forward");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
delay(5000);
  // Handle back movement
  Serial.println("right");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
delay(5000);
  // Handle forward movement
  Serial.println("left");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(ENA, 100);
  analogWrite(ENB, 100);
delay(5000);
}
