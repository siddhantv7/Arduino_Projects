
#define USE_ARDUINO_INTERRUPTS false
#include <PulseSensorPlayground.h>

const int OUTPUT_TYPE = SERIAL_PLOTTER;

const int PULSE_INPUT = A0;
const int PULSE_BLINK = 2;
const int PULSE_FADE = 5;
const int THRESHOLD = 550;   // Adjust this number to avoid noise when idle

byte samplesUntilReport;
const byte SAMPLES_PER_SERIAL_SAMPLE = 10;

PulseSensorPlayground pulseSensor;

void setup() {
  Serial.begin(115200);

  // Configure the PulseSensor manager.
  pulseSensor.analogInput(PULSE_INPUT);
  pulseSensor.blinkOnPulse(PULSE_BLINK);
  pulseSensor.fadeOnPulse(PULSE_FADE);

  pulseSensor.setSerial(Serial);
  pulseSensor.setOutputType(OUTPUT_TYPE);
  pulseSensor.setThreshold(THRESHOLD);

  // Skip the first SAMPLES_PER_SERIAL_SAMPLE in the loop().
  samplesUntilReport = SAMPLES_PER_SERIAL_SAMPLE;

  // Now that everything is ready, start reading the PulseSensor signal.
  //  if (!pulseSensor.begin()) {
  //    
  //    for(;;) {
  //      // Flash the led to show things didn't work.
  //      digitalWrite(PULSE_BLINK, LOW);
  //      delay(50); 
  //      Serial.println('!');
  //      digitalWrite(PULSE_BLINK, HIGH);
  //      delay(50);
  //    }
  //  }
}

void loop() {
  
  if (pulseSensor.sawNewSample()) {
    if (--samplesUntilReport == (byte) 0) {
      samplesUntilReport = SAMPLES_PER_SERIAL_SAMPLE;
//      pulseSensor.outputSample();
      if (pulseSensor.sawStartOfBeat()) {
//        pulseSensor.outputBeat();
          int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".
                                                         // "myBPM" hold this BPM value now. 
//           Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
//           Serial.print("BPM: ");                        // Print phrase "BPM: " 
           Serial.println(myBPM);                     
      }
    }
  }

}
