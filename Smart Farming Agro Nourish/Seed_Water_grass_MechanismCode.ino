#include <AFMotor.h>
#include <Servo.h>

// Initialize motors pin
AF_DCMotor motor1(1);      // Motor 1 and 2 are controlled by pin 1
AF_DCMotor motor2(4);      // Motor 3 and 4 are controlled by pin 4
Servo servoMotor;          // seed sowing Motor is going to control by pin 3
AF_DCMotor waterPump(2);   // water pump is going to controlled by pin 2
AF_DCMotor GrassCutter(3); // water pump is going to controlled by pin 2

char val;
int Speeed = 255;
int pos = 0;               // variable to store the servo position
bool isSeedSowing = false; // add this global variable
bool indicator = false;

void setup()
{
    Serial.begin(9600);    // rate of transferring data from one device to another (phone);
    servoMotor.attach(10); // attaches the servo on pin 3 to the servo object
    servoMotor.write(0);
}

void loop()
{
    if (Serial.available() > 0)
    {
        // reading the value from the serial
        val = Serial.read();
        Serial.println(val); // displaying the value from serial

        if (val == 'F')
        {
            forward();
        }
        else if (val == 'B')
        {
            back();
        }
        else if (val == 'L')
        {
            left();
        }
        else if (val == 'R')
        {
            right();
        }
        else if (val == 'H')
        {
            seedSowing();
        }
        else if (val == 'A')
        {
            StopSeedSowing();
        }
        else if (val == 'X')
        {
            stop();
        }
        else if (val == 'G')
        {
            waterPumpOn();
        }
        else if (val == 'D')
        {
            waterPumpOff();
        } // grass cutter program
        else if (val == 'K')
        {
            GrassCutterOn();
        }
        else if (val == 'J')
        {
            GrassCutterOff();
        }
    }
    // if(indicator = isSeedSowing)
    // {
    //   servoMotor.write(0);
    // }

    if (isSeedSowing)
    {
        // servoMotor.write(0);
        for (pos = 0; pos <= 33; pos += 1)
        {                          // goes from 0 degrees to 180 degrees
            servoMotor.write(pos); // tell servo to go to position in variable 'pos'
            delay(10);             // waits 15ms for the servo to reach the position
        }
        for (pos = 33; pos >= 0; pos -= 1)
        {                          // goes from 180 degrees to 0 degrees
            servoMotor.write(pos); // tell servo to go to position in variable 'pos'
            delay(10);             // waits 15ms for the servo to reach the position
        }
    }
}

void forward()
{
    Serial.println("Forward mai hu");
    motor1.setSpeed(Speeed);
    motor1.run(FORWARD);
    motor2.setSpeed(Speeed);
    motor2.run(FORWARD);
}

void back()
{
    Serial.println("back mai hu");
    motor1.setSpeed(Speeed);
    motor1.run(BACKWARD);
    motor2.setSpeed(Speeed);
    motor2.run(BACKWARD);
}

void right()
{
    Serial.println("right mai hu");
    motor1.setSpeed(Speeed);
    motor1.run(FORWARD);
    motor2.setSpeed(Speeed);
    motor2.run(BACKWARD);
}

void left()
{
    Serial.println("left mai hu");
    motor1.setSpeed(Speeed);
    motor1.run(BACKWARD);
    motor2.setSpeed(Speeed);
    motor2.run(FORWARD);
}

void stop()
{
    Serial.println("Stop mai hu");
    motor1.setSpeed(0);
    motor1.run(RELEASE);
    motor2.setSpeed(0);
    motor2.run(RELEASE);
}

void seedSowing()
{
    Serial.println("Seed Sow Kr rha hu");
    isSeedSowing = true;
}

void StopSeedSowing()
{
    Serial.println("Seed Sowing Stopped");
    isSeedSowing = false;
}

void waterPumpOn()
{
    waterPump.setSpeed(Speeed);
    waterPump.run(FORWARD);
}

void waterPumpOff()
{
    waterPump.setSpeed(0);
    waterPump.run(RELEASE);
}

void GrassCutterOn()
{
    GrassCutter.setSpeed(Speeed);
    GrassCutter.run(FORWARD);
}

void GrassCutterOff()
{
    GrassCutter.setSpeed(0);
    GrassCutter.run(RELEASE);
}
