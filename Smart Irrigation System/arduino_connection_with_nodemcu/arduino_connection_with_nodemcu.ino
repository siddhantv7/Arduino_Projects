#include<string.h>
#define led 5
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

}
void loop() {
  // put your main code here, to run repeatedly:
  char buffer[20]="";
  int val;
  if(Serial.available()>0){
    char data = Serial.read();
    Serial.readBytesUntil('\n',buffer, 20);
    Serial.println(data);
    val = int(data);
    Serial.println(val);
    if (val == 49 ){
      digitalWrite(led, HIGH);
      delay(1000);
      digitalWrite(led, LOW);
      delay(1000);
    }
    }
  }
  
