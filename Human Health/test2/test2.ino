void setup() {
  Serial.begin(115200);

}
void loop() {
char buffer[20] = "";
  if (Serial.available() > 0) {
    String  data = Serial.readString();
    Serial.readBytesUntil('\n', buffer, 20);
    Serial.println(data);
  }
}
