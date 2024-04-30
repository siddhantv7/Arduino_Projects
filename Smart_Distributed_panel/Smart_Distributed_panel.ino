
#define voltage1 16
#define voltage2 17
#define voltage3 18
#define voltage4 19
#define voltage5 21
#define voltage6 22
#define current1 32
#define current2 33
#define current3 34
#define current4 35
#define current5 27
#define current6 14
#define loadOutput1 12
#define loadOutput2 13

int  voltageInput1;
int  voltageInput2;
int  voltageInput3;
int  voltageInput4;
int  voltageInput5;
int  voltageInput6;
int  currentInput1;
int  currentInput2;
int  currentInput3;
int  currentInput4;
int  currentInput5;
int  currentInput6;
int  load1;
int  load2;




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(voltage1, INPUT);
  pinMode(voltage2, INPUT);
  pinMode(voltage3, INPUT);
  pinMode(voltage4, INPUT);
  pinMode(voltage5, INPUT);
  pinMode(voltage6, INPUT);
  pinMode(current1, INPUT);
  pinMode(current2, INPUT);
  pinMode(current3, INPUT);
  pinMode(current4, INPUT);
  pinMode(current5, INPUT);
  pinMode(current6, INPUT);
  pinMode(loadOutput1, OUTPUT);
  pinMode(loadOutput2, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  // 0,2,4,5,6,
  //34 to 39 input only
  voltageInput1 = analogRead(voltage1);
  Serial.print(voltageInput1);
  voltageInput2 = analogRead(voltage2);
  Serial.print(voltageInput2);
  voltageInput3 = analogRead(voltage3);
  Serial.print(voltageInput3);
  voltageInput4 = analogRead(voltage4);
  Serial.print(voltageInput4);
  voltageInput5 = analogRead(voltage5);
  Serial.print(voltageInput5);
  voltageInput6 = analogRead(voltage6);
  Serial.print(voltageInput6);
  currentInput1 = analogRead(current1);
  Serial.print(currentInput1);
  currentInput2 = analogRead(current2);
  Serial.print(currentInput2);
  currentInput3 = analogRead(current3);
  Serial.print(currentInput3);
  currentInput4 = analogRead(current4);
  Serial.print(currentInput4);
  currentInput5 = analogRead(current5);
  Serial.print(currentInput5);
  currentInput6 = analogRead(current6);
  Serial.print(currentInput6);
  digitalWrite(load1, HIGH);
  delay(10000);
  digitalWrite(load1, LOW );
  digitalWrite(load2, HIGH);
  delay(10000);
  digitalWrite(load2, LOW);
  digitalWrite(load1, HIGH);
  digitalWrite(load2, HIGH);
  delay(10000);
  digitalWrite(load1, LOW);
  digitalWrite(load2, LOW);


}
