

// set pin numbers

const int soundPin =  5;       // the number of the LED pin
unsigned int soundPin1 =  A0;       // the number of the LED pin

void setup() {
  Serial.begin(9600);
  pinMode(soundPin, INPUT);
  pinMode(soundPin1, INPUT);
  Serial.print("Analog value: ");
}

void loop() {
//  int sound = digitalRead(soundPin);
  int sound1 = analogRead(soundPin1);


  Serial.println(sound1);
  
  delay(100);
}
