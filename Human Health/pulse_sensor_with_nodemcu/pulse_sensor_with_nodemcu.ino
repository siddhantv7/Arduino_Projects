


//  Variables
int PulseSensorPurplePin = A0;
int LED13 = 13;


int Signal;
int Threshold = 300;


// The SetUp Function:
void setup() {
  pinMode(LED13, OUTPUT);
  Serial.begin(9600);
}

// The Main Loop Function
void loop() {
  int myBPM = 0;
  int i = 60;
  while (i != 1) {
    for (int x = 4; x != 1; x--) {
      Signal = analogRead(PulseSensorPurplePin);
      if (Signal > 100) {
        myBPM = myBPM + 1;
      } else {
        myBPM = myBPM - 1;

      }
      delay(60);
    }
    i--;
    delay(1000);
  }

  Serial.println("♥  A HeartBeat Happened ! ");
  Serial.print("BPM: ");
  Serial.println(myBPM);

}
