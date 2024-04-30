#include <Arduino.h>

// Define the pin connected to the built-in LED on ESP32
#define LED_BUILTIN 2 // Typically, the built-in LED on ESP32 is connected to pin 2

void setup() {
  // Initialize digital pin LED_BUILTIN as an output
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // Turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);
  // Wait for a short duration
  delay(100);
  // Turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);
  // Wait for a short duration
  delay(100);
}
