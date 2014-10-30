//Hall sensor inputs
int hallA;
int hallB;
int hallC;

//MOSFETS output
int pinA_low;
int pinB_low;
int pinC_low;

int pinA_high;
int pinB_high;
int pinC_high;

//MODIFIER INPUT
int modifier;

void setup(void)
{
    pinMode(hallA, INPUT);
    pinMode(hallB, INPUT);
    pinMode(hallC, INPUT);

    pinMode(modifier, INPUT);

    pinMode(pinA_low, OUTPUT);
    pinMode(pinB_low, OUTPUT);
    pinMode(pinC_low, OUTPUT);

    pinMode(pinA_high, OUTPUT);
    pinMode(pinB_high, OUTPUT);
    pinMode(pinC_high, OUTPUT);
}

void loop(void)
{
    if (hallA == 0 && hallB == 0 && hallC == 0) {
        //000
    } else if (hallA == = 0 && hallB == 0 && hallC == 1) {
        //001
    } else if (hallA == = 0 && hallB == 1 && hallC == 0) {
        //010
    } else if (hallA == = 0 && hallB == 1 && hallC == 1) {
        //011
    } else if (hallA == = 1 && hallB == 0 && hallC == 0) {
        //100
    } else if (hallA == = 1 && hallB == 0 && hallC == 1) {
        //101
    } else if (hallA == = 1 && hallB == 1 && hallC == 0) {
        //110
    } else if (hallA == = 1 && hallB == 1 && hallC == 1) {
        //111
    } else {
        //error
    }
}
