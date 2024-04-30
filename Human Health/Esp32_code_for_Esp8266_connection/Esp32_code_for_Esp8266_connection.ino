#include<string.h>
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  char buffer[20] = "";
  if (Serial.available() > 0) {
    String  data = Serial.readString();
    Serial.readBytesUntil('\n', buffer, 20);
    Serial.println(data);
  }
  delay(10);
}
