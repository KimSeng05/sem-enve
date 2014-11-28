int hallA=1;
int hallB=2;

int readA=0;
int readB=0;

int gHA=3;
int gHB=5;
int gHC=6;
int gLA=9;
int gLB=10;
int gLC=11;

void setup()
{
  pinMode(hallA, INPUT);
  pinMode(hallB, INPUT);
  pinMode(gHA, OUTPUT);
  pinMode(gHB, OUTPUT);
  pinMode(gHC, OUTPUT);
  pinMode(gLA, OUTPUT);
  pinMode(gLB, OUTPUT);
  pinMode(gLC, OUTPUT);
}

void loop()
{
  readA=digitalRead(hallA);
  readB=digitalRead(hallB);

  if(readA==HIGH && readB==LOW) {
    digitalWrite(gHA, HIGH);
    digitalWrite(gHB, LOW);
    digitalWrite(gHC, LOW);
    digitalWrite(gLA, LOW);
    digitalWrite(gLB, LOW);
    digitalWrite(gLC, HIGH);
    //delay(Prd*1000);
    //digitalWrite(gLB, LOW);
    //digitalWrite(gHA, HIGH);
    //digitalWrite(gLC, HIGH);
  } else if(readA=HIGH && readB==HIGH) {
    digitalWrite(gHA, LOW);
    digitalWrite(gHB, HIGH);
    digitalWrite(gHC, LOW);
    digitalWrite(gLA, LOW);
    digitalWrite(gLB, LOW);
    digitalWrite(gLC, HIGH);
  } else if(readA=LOW && readB==HIGH) {
    digitalWrite(gHA, LOW);
    digitalWrite(gHB, HIGH);
    digitalWrite(gHC, LOW);
    digitalWrite(gLA, HIGH);
    digitalWrite(gLB, LOW);
    digitalWrite(gLC, LOW);
    //delay(Prd*1000);
    //digitalWrite(gLA, HIGH);
    //digitalWrite(gHC, HIGH);
  } else if(readA==LOW && readB==LOW) {
    digitalWrite(gHA, LOW);
    digitalWrite(gHB, LOW);
    digitalWrite(gHC, HIGH);
    digitalWrite(gLA, LOW);
    digitalWrite(gLB, HIGH);
    digitalWrite(gLC, LOW);
  } else {
    digitalWrite(gHA, LOW);
    digitalWrite(gHB, LOW);
    digitalWrite(gHC, LOW);
    digitalWrite(gLA, LOW);
    digitalWrite(gLB, LOW);
    digitalWrite(gLC, LOW);
  }
}
