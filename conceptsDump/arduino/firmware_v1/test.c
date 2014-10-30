//Hall sensor inputs
int hallA_sensor;
int hallB_sensor;
int hallC_sensor;

//Initialize Hall sensor state variables
int hallA_state = 0;
int hallB_state = 0;
int hallC_state = 0;

//MOSFETS output
int pinA_low;
int pinB_low;
int pinC_low;

int pinA_high;
int pinB_high;
int pinC_high;

//MODIFIER INPUT
int pinSensor;
int speed = 0;
int correction;

int ANALOG_WRITE_READ = 1024/256;

void setup(void)
{
    pinMode(hallA_sensor, INPUT);
    pinMode(hallB_sensor, INPUT);
    pinMode(hallC_sensor, INPUT);
    pinMode(correction, INPUT);
    pinMode(pinSensor, INPUT);

    pinMode(pinA_low, OUTPUT);
    pinMode(pinB_low, OUTPUT);
    pinMode(pinC_low, OUTPUT);

    pinMode(pinA_high, OUTPUT);
    pinMode(pinB_high, OUTPUT);
    pinMode(pinC_high, OUTPUT);
}

void loop(void)
{
    speed = analogRead(pinSensor)/ANALOG_WRITE_READ;

    //Read the hall sensor values
    hallA_state = digitalRead(hallA_sensor);
    hallB_state = digitalRead(hallB_sensor);
    hallC_state = digitalRead(hallC_sensor);

    //Hopefully clockwise commutation
    if (hallA_state == 0 && hallB_state == 0 && hallC_state == 0) { //000
        analogWrite(pinA_low, 0);
        analogWrite(pinB_low, 0);
        analogWrite(pinC_low, 0);
        analogWrite(pinA_high, 0);
        analogWrite(pinB_high, 0);
        analogWrite(pinC_high, 0);
    } else if (hallA_state == 0 && hallB_state == 0 && hallC_state == 1) { //001
        analogWrite(pinC_high, speed);
        analogWrite(pinB_low, 255);
    } else if (hallA_state == 0 && hallB_state == 1 && hallC_state == 0) { //010
        analogWrite(pinB_high, speed);
        analogWrite(pinA_low, 255);
    } else if (hallA_state == 0 && hallB_state == 1 && hallC_state == 1) { //011
        analogWrite(pinC_high, speed);
        analogWrite(pinA_low, 255);
    } else if (hallA_state == 1 && hallB_state == 0 && hallC_state == 0) { //100
        analogWrite(pinA_high, speed);
        analogWrite(pinC_low, 255);
    } else if (hallA_state == 1 && hallB_state == 0 && hallC_state == 1) { //101
        analogWrite(pinA_high, speed);
        analogWrite(pinB_low, 255);
    } else if (hallA_state == 1 && hallB_state == 1 && hallC_state == 0) { //110
        analogWrite(pinB_high, speed);
        analogWrite(pinC_low, 255);
    } else if (hallA_state == 1 && hallB_state == 1 && hallC_state == 1) { //111
        //error
    } else {
        //error
    }
}
