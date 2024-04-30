void setup()
{
  Serial.begin(9600);
}
void loop()
{

  int b = digitalRead(7);

  Serial.print("IR1:" );
  Serial.println(b);
  delayMicroseconds(500);
}
