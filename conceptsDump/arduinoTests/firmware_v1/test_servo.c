#include <Servo.h>

Servo bldc_motor;

int motorPin;

void Setup()
{
    bldc_motor.attach(motorPin);
}

void loop()
{
    bldc_motor.writeMicroseconds(1500);//provides a "neutral" pulse. The ESC won't start without this.
    for (int i = 4; i >= 0; i --) {//countdown timer
        delay(1000);
    }

    while(1) {
        for (int i = 1500; i <= 2000; i++) {
            int speed_value = map (i, 1500, 2000, 0, 100); //maps the signal pulse to a percentage
            bldc_motor.writeMicroseconds (i); //actually write the value to the motor
        }

         for (int i = 4; i >= 0; i --) { //countdown timer
            delay (1000);
         }

         bldc_motor.writeMicroseconds (1000); //full reverse. The ESC will automatically brake the motor.
         delay (500); //small delay to let things happen
         bldc_motor.writeMicroseconds (1500); //give a neutral signal
         delay (3000); //keep it that way for a while

        for (int i = 1500; i >= 1000; i --) {
            int speed_value = map (i, 1500, 1000, 0, 100); //maps the signal pulse to a percentage
             bldc_motor.writeMicroseconds (i); //actually write the value to the motor
             delay(10);// small delay so you can see what's happening
        }

        delay (3000); //keep it at 100% backward for a while
        bldc_motor.writeMicroseconds (1500);
        delay (3000);
    }
}
