#define gHA
#define gHB
#define gHC
#define gLA
#define gLB
#define gLC

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
    digitalWrite(gHB, 0);
    digitalWrite(gHC, 0);
    digitalWrite(gLA, 0);
    digitalWrite(gLC, 0);
    digitalWrite(gHA, HIGH);
    digitalWrite(gLB, HIGH);
    delay(safety_delay*1000);
}

void commute_AC()
{
    digitalWrite(gHB, 0);
    digitalWrite(gHC, 0);
    digitalWrite(gLA, 0);
    digitalWrite(gLB, 0);
    digitalWrite(gHA, HIGH);
    digitalWrite(gLC, HIGH);
    delay(safety_delay*1000);
}

void commute_BA()
{
    digitalWrite(gHA, 0);
    digitalWrite(gHC, 0);
    digitalWrite(gLB, 0);
    digitalWrite(gLC, 0);
    digitalWrite(gHB, HIGH);
    digitalWrite(gLA, HIGH);
    delay(safety_delay*1000);
}

void commute_BC()
{
    digitalWrite(gHA, 0);
    digitalWrite(gHC, 0);
    digitalWrite(gLA, 0);
    digitalWrite(gLB, 0);
    digitalWrite(gHB, HIGH);
    digitalWrite(gLC, HIGH);
    delay(safety_delay*1000);
}

void commute_CA()
{
    digitalWrite(gHA, 0);
    digitalWrite(gHB, 0);
    digitalWrite(gLB, 0);
    digitalWrite(gLC, 0);
    digitalWrite(gHC, HIGH);
    digitalWrite(gLA, HIGH);
    delay(safety_delay*1000);
}

void commute_CB()
{
    digitalWrite(gHA, 0);
    digitalWrite(gHB, 0);
    digitalWrite(gLA, 0);
    digitalWrite(gLC, 0);
    digitalWrite(gHC, HIGH);
    digitalWrite(gLB, HIGH);
    delay(safety_delay*1000);
}

