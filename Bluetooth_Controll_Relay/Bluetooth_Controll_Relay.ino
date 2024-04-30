int relay1 = 5;
int relay2 = 6;
int relay3 = 7;
int relay4 = 8;

bool relayState1 = false;
bool relayState2 = false;
bool relayState3 = false;
bool relayState4 = false;

void setup() {
  // put your setup code  here, to run once:
  Serial.begin(9600);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
}

void  loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()  > 0)
  {
    int Incoming_value = Serial.read();
    Serial.print(Incoming_value);
    Serial.print("/n");
    switch (Incoming_value) {
      case 49:
        if (relayState1 == false) {
          digitalWrite(relay1, HIGH);
          Serial.println("LED1 ON!");
          relayState1 = true;
        }
        else if (relayState1 == true) {
          digitalWrite(relay1, LOW);
          Serial.println("LED1 OFF!");
          relayState1 = false;
        }
        break;
      case 50:
        if (relayState2 == false) {
          digitalWrite(relay2, HIGH);
          Serial.println("LED2 ON!");
          relayState2 = true;
        }
        else if (relayState2 == true) {
          digitalWrite(relay2, LOW);
          Serial.println("LED2 OFF!");
          relayState2 = false;
        }
        break;
      case 51:
        if (relayState3 == false) {
          digitalWrite(relay3, HIGH);
          Serial.println("LED3 ON!");
          relayState3 = true;
        }
        else if (relayState3 == true) {
          digitalWrite(relay3, LOW);
          Serial.println("LED3 OFF!");
          relayState3 = false;
        }
        break;
      case 52:
        if (relayState4 == false) {
          digitalWrite(relay4, HIGH);
          Serial.println("LED4 ON!");
          relayState4 = true;
        }
        else if (relayState4 == true) {
          digitalWrite(relay4, LOW);
          Serial.println("LED4 OFF!");
          relayState4 = false;
        }
        break;
      default:
        // statements
        break;
    }
  }
}
