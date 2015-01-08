#define gHA
#define gHB
#define gHC
#define gLA
#define gLB
#define gLC

int deadtime_ms=100;
int on_ms=50;

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
    delay(deadtime_ms);
    digitalWrite(gHB, LOW);
    digitalWrite(gHC, LOW);
    digitalWrite(gLA, LOW);
    digitalWrite(gLC, LOW);
    digitalWrite(gHA, HIGH);
    digitalWrite(gLB, HIGH);
    delay(on_ms_);
    digitalWrite(gHA, LOW);
    digitalWrite(gLB, LOW);
}

void commute_AC()
{
    delay(deadtime_ms);
    digitalWrite(gHB, LOW);
    digitalWrite(gHC, LOW);
    digitalWrite(gLA, LOW);
    digitalWrite(gLB, LOW);
    digitalWrite(gHA, HIGH);
    digitalWrite(gLC, HIGH);
    delay(on_ms_);
    digitalWrite(gHA, LOW);
    digitalWrite(gLC, LOW);
}

void commute_BA()
{
    delay(deadtime_ms);
    digitalWrite(gHA, LOW);
    digitalWrite(gHC, LOW);
    digitalWrite(gLB, LOW);
    digitalWrite(gLC, LOW);
    digitalWrite(gHB, HIGH);
    digitalWrite(gLA, HIGH);
    delay(on_ms_);
    digitalWrite(gHB, LOW);
    digitalWrite(gLA, LOW);
}

void commute_BC()
{
    delay(deadtime_ms);
    digitalWrite(gHA, LOW);
    digitalWrite(gHC, LOW);
    digitalWrite(gLA, LOW);
    digitalWrite(gLB, LOW);
    digitalWrite(gHB, HIGH);
    digitalWrite(gLC, HIGH);
    delay(on_ms_);
    digitalWrite(gHB, LOW);
    digitalWrite(gLC, LOW);
}

void commute_CA()
{
    delay(deadtime_ms);
    digitalWrite(gHA, LOW);
    digitalWrite(gHB, LOW);
    digitalWrite(gLB, LOW);
    digitalWrite(gLC, LOW);
    digitalWrite(gHC, HIGH);
    digitalWrite(gLA, HIGH);
    delay(on_ms_);
    digitalWrite(gHC, LOW);
    digitalWrite(gLA, LOW);
}

void commute_CB()
{
    delay(deadtime_ms);
    digitalWrite(gHA, LOW);
    digitalWrite(gHB, LOW);
    digitalWrite(gLA, LOW);
    digitalWrite(gLC, LOW);
    digitalWrite(gHC, HIGH);
    digitalWrite(gLB, HIGH);
    delay(on_ms_);
    digitalWrite(gHC, LOW);
    digitalWrite(gLB, LOW);
}

