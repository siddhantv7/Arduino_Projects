/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp8266-relay-module-ac-web-server/
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

void setup() {
  Serial.begin(115200);
  pinMode(D8, OUTPUT);
}

void loop() {

  digitalWrite(D8, LOW);
  delay(10000);
  digitalWrite(D8, HIGH);
  delay(10000);

}
