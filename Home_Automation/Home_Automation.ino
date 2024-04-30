
// Include Libraries
#include "Arduino.h"
#include "Wire.h"
#include "SPI.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"


// Pin Definitions
#define FINGERPRINTSCANNER_3V3_PIN_RX  12
#define FINGERPRINTSCANNER_3V3_PIN_TX 2
#define OLED128X64_PIN_RST  0
#define OLED128X64_PIN_DC 4
#define OLED128X64_PIN_CS 5



// Global variables and defines

// object initialization
#define SSD1306_LCDHEIGHT 64
Adafruit_SSD1306 oLed128x64(OLED128X64_PIN_DC, OLED128X64_PIN_RST, OLED128X64_PIN_CS);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    oLed128x64.begin(SSD1306_SWITCHCAPVCC);  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
    oLed128x64.clearDisplay(); // Clear the buffer.
    oLed128x64.display();
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1')
    {
    // Disclaimer: The Fingerprint Scanner - TTL (GT-511C3) is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    else if(menuOption == '2') {
    // Monochrome 1.3 inch 128x64 OLED graphic display - Test Code
    oLed128x64.setTextSize(1);
    oLed128x64.setTextColor(WHITE);
    oLed128x64.setCursor(0, 10);
    oLed128x64.clearDisplay();
    oLed128x64.println("Circuito.io Rocks!");
    oLed128x64.display();
    delay(1);
    oLed128x64.startscrollright(0x00, 0x0F);
    delay(2000);
    oLed128x64.stopscroll();
    delay(1000);
    oLed128x64.startscrollleft(0x00, 0x0F);
    delay(2000);
    oLed128x64.stopscroll();
    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) Fingerprint Scanner - TTL (GT-511C3)"));
    Serial.println(F("(2) Monochrome 1.3 inch 128x64 OLED graphic display"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
          Serial.println(F("Now Testing Fingerprint Scanner - TTL (GT-511C3) - note that this component doesn't have a test code"));
        else if(c == '2') 
          Serial.println(F("Now Testing Monochrome 1.3 inch 128x64 OLED graphic display"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}
