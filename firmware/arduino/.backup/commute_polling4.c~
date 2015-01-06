#define gHA
#define gHB
#define gHC
#define gLA
#define gLB
#define gLC

int speed=255;
int safety_delay=1;

void setup()
{
    pinMode(gHA, OUTPUT);
    pinMode(gHB, OUTPUT);
    pinMode(gHC, OUTPUT);
    pinMode(gLA, OUTPUT);
    pinMode(gLB, OUTPUT);
    pinMode(gLC, OUTPUT);
}

void loop()
{
    commute_AB();
    commute_AC();
    commute_BC();
    commute_BA();
    commute_CA();
    commute_CB();
}

void commute_AB()
{
    analogWrite(gHB, 0);
    analogWrite(gHC, 0);
    analogWrite(gLA, 0);
    analogWrite(gLC, 0);
    analogWrite(gHA, speed);
    analogWrite(gLB, 255);
    delay(safety_delay*1000);
}

void commute_AC()
{
    analogWrite(gHB, 0);
    analogWrite(gHC, 0);
    analogWrite(gLA, 0);
    analogWrite(gLB, 0);
    analogWrite(gHA, speed);
    analogWrite(gLC, 255);
    delay(safety_delay*1000);
}

void commute_BA()
{
    analogWrite(gHA, 0);
    analogWrite(gHC, 0);
    analogWrite(gLB, 0);
    analogWrite(gLC, 0);
    analogWrite(gHB, speed);
    analogWrite(gLA, 255);
    delay(safety_delay*1000);
}

void commute_BC()
{
    analogWrite(gHA, 0);
    analogWrite(gHC, 0);
    analogWrite(gLA, 0);
    analogWrite(gLB, 0);
    analogWrite(gHB, speed);
    analogWrite(gLC, 255);
    delay(safety_delay*1000);
}

void commute_CA()
{
    analogWrite(gHA, 0);
    analogWrite(gHB, 0);
    analogWrite(gLB, 0);
    analogWrite(gLC, 0);
    analogWrite(gHC, speed);
    analogWrite(gLA, 255);
    delay(safety_delay*1000);
}

void commute_CB()
{
    analogWrite(gHA, 0);
    analogWrite(gHB, 0);
    analogWrite(gLA, 0);
    analogWrite(gLC, 0);
    analogWrite(gHC, speed);
    analogWrite(gLB, 255);
    delay(safety_delay*1000);
}

