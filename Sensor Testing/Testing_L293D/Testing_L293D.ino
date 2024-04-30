#include <AFMotor.h>
AF_DCMotor motor(1, MOTOR12_64KHZ);
void setup()
{
    //Set initial speed of the motor & stop
    motor.setSpeed(150);
    motor.run(RELEASE);
}
void loop()
{


    // Turn on motor
    motor.run(FORWARD);  
    delay(2000);
    motor.run(RELEASE);
    delay(1000);
        motor.run(BACKWARD); 
    delay(2000);   
}
