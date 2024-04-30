void setup()
{
  // initialize the serial communication:
  Serial.begin(115200);
  pinMode(25, INPUT); // Setup for leads off detection LO +
  pinMode(26, INPUT); // Setup for leads off detection LO -

}

void loop() {

  if ((digitalRead(25) == 1) || (digitalRead(26) == 1)) {
    Serial.println('!');
  }
  else {
    // send the value of analog input 0:
    Serial.println(analogRead(34));
  }
  //Wait for a bit to keep serial data from saturating
  delay(1);
}
