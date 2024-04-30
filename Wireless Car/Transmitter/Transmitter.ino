
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const int x_out = A0;
const int y_out = A1;
RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
struct data {
  int xAxis;
  int yAxis;

};
data send_data;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {

  send_data.xAxis = analogRead(x_out);
  send_data.yAxis = analogRead(y_out);
  Serial.print("X: ");
  Serial.print(send_data.xAxis);
  Serial.print("--Y: ");
  Serial.println(send_data.yAxis);

  radio.write(&send_data, sizeof(data));
//  delay(100);
}
