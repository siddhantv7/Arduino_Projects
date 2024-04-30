// Include Libraries
#include "Arduino.h"
#include "RFID.h"
#include "Servo.h"

// Pin Definitions
#define IROBJAVOID_1_PIN_OUT  5
#define IROBJAVOID_2_PIN_OUT  4
#define RFID_PIN_RST  0
#define RFID_PIN_SDA  2
#define SERVO360MICRO_PIN_SIG 15

// Global variables and defines

// object initialization
RFID rfid(RFID_PIN_SDA, RFID_PIN_RST);
Servo servo360Micro;

// define vars for testing menu
const int timeout = 10000; // define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup()
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial)
        ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");

    pinMode(IROBJAVOID_1_PIN_OUT, INPUT);
    pinMode(IROBJAVOID_2_PIN_OUT, INPUT);
    // initialize RFID module
    rfid.init();
    menuOption = menu();
}

// Main logic of your circuit. It defines the interaction between the components you selected.
// After setup, it runs over and over again, in an eternal loop.
void loop()
{
    if (menuOption == '1')
    {
        // IR Obstacle Avoidance Sensor #1 - Test Code
        // Read IR obstacle Sensor. irObjAvoid_1Var will be '1' if an Obstacle was detected
        // Use the onboard trimmer to set the distance of alert
        bool irObjAvoid_1Var = !digitalRead(IROBJAVOID_1_PIN_OUT);
        Serial.print(F("ObjAvoid: "));
        Serial.println(irObjAvoid_1Var);
    }
    else if (menuOption == '2')
    {
        // IR Obstacle Avoidance Sensor #2 - Test Code
        // Read IR obstacle Sensor. irObjAvoid_2Var will be '1' if an Obstacle was detected
        // Use the onboard trimmer to set the distance of alert
        bool irObjAvoid_2Var = !digitalRead(IROBJAVOID_2_PIN_OUT);
        Serial.print(F("ObjAvoid: "));
        Serial.println(irObjAvoid_2Var);
    }
    else if (menuOption == '3')
    {
        // RFID Card Reader - RC522 - Test Code
        // Read RFID tag if present
        String rfidtag = rfid.readTag();
        // print the tag to the serial monitor if one was discovered
        rfid.printTag(rfidtag);

        // If RFID tag is detected, open the servo
        if (rfidtag.length() > 0)
        {
            openServo();
        }
    }
    else if (menuOption == '4')
    {
        // Continuous Rotation Micro Servo - FS90R - Test Code
        // The servo will rotate CW in full speed, CCW in full speed, and will stop with an interval of 2000 milliseconds (2 seconds)
        servo360Micro.attach(SERVO360MICRO_PIN_SIG); // 1. attach the servo to correct pin to control it.
        servo360Micro.write(180);                    // 2. turns servo CW in full speed. change the value in the brackets (180) to change the speed. As these numbers move closer to 90, the servo will move slower in that direction.
        delay(2000);                                // 3. waits 2000 milliseconds (2 sec). change the value in the brackets (2000) for a longer or shorter delay in milliseconds.
        servo360Micro.write(0);                      // 4. turns servo CCW in full speed. change the value in the brackets (0) to change the speed. As these numbers move closer to 90, the servo will move slower in that direction.
        delay(2000);                                // 5. waits 2000 milliseconds (2 sec). change the value in the brackets (2000) for a longer or shorter delay in milliseconds.
        servo360Micro.write(90);                     // 6. sending 90 stops the servo
        delay(2000);                                 // 7. waits 2000 milliseconds (2 sec). change the value in the brackets (2000) for a longer or shorter delay in milliseconds.
        servo360Micro.detach();                       // 8. release the servo to conserve power. When detached the servo will NOT hold its position under stress.
    }

    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
}

// Open the servo
void openServo()
{
    servo360Micro.attach(SERVO360MICRO_PIN_SIG);
    servo360Micro.write(180); // Adjust the angle as needed
    delay(2000);
    servo360Micro.detach();
}

// Menu function for selecting the components to be tested
// Follow the serial monitor for instructions
char menu()
{
    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) IR Obstacle Avoidance Sensor #1"));
    Serial.println(F("(2) IR Obstacle Avoidance Sensor #2"));
    Serial.println(F("(3) RFID Card Reader - RC522"));
    Serial.println(F("(4) Continuous Rotation Micro Servo - FS90R"));
    Serial.println(F("(menu) send anything else or press the on-board reset button\n"));
    while (!Serial.available());

    // Read data from the serial monitor if received
    while (Serial.available())
    {
        char c = Serial.read();
        if (isAlphaNumeric(c))
        {

            if (c == '1')
                Serial.println(F("Now Testing IR Obstacle Avoidance Sensor #1"));
            else if (c == '2')
                Serial.println(F("Now Testing IR Obstacle Avoidance Sensor #2"));
            else if (c == '3')
                Serial.println(F("Now Testing RFID Card Reader - RC522"));
            else if (c == '4')
                Serial.println(F("Now Testing Continuous Rotation Micro Servo - FS90R"));
            else
            {
                Serial.println(F("Illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}
