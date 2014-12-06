#include <LiquidCrystal.h>

#define checkLED 2

//define Gate Input pins
#define gHA A0
#define gLA A1
#define gHB A2
#define gLB A3
#define gLC A4
#define gHC A5

LiquidCrystal lcd(4,5,6,7,8,9);

unsigned long int inSignal=0;
int lastRun=0;

void setup()
{
  //debugging 
  lcd.begin(16,2);
  pinMode(checkLED, OUTPUT);
  
  pinMode(gHA, OUTPUT);
  pinMode(gHB, OUTPUT);
  pinMode(gHC, OUTPUT);
  pinMode(gLA, OUTPUT);
  pinMode(gLB, OUTPUT);
  pinMode(gLC, OUTPUT);
}

void loop()
{
  //Activate checkLED
  digitalWrite(checkLED, LOW);
  delay(0.5*1000);
  digitalWrite(checkLED, HIGH);
  
  //if (lastRun==0) {
  //  inSignal=phase_A();
  //  lastRun=1;
  //}else if (lastRun==1) {
  //  inSignal=phase_B();
  //  lastRun=2;
  //}else if (lastRun==2) {
  //  inSignal=phase_C();
  //  lastRun=0;
  //}else {
  //  lcd.setCursor(0,1);
  // lcd.print("ERR");
  //  inSignal=0;
  //}
  
  inSignal=phase_AB();
  
  //print to LCD
  lcd.setCursor(0,0);
  lcd.print("t");
  lcd.print(millis()/1000);
  lcd.print(" s");
  lcd.print(inSignal);
  
  delay(1*1000);
  lcd.clear();
}

unsigned long int phase_AB()
{
  digitalWrite(gHA, HIGH);
  digitalWrite(gHB, LOW);
  digitalWrite(gHC, LOW);
  digitalWrite(gLA, LOW);
  digitalWrite(gLB, HIGH);
  digitalWrite(gLC, LOW);
  
  unsigned long int signal=2100100;
  return signal;
}

unsigned long int phase_A()
{
  digitalWrite(gHA, HIGH);
  digitalWrite(gHB, LOW);
  digitalWrite(gHC, LOW);
  digitalWrite(gLA, LOW);
  digitalWrite(gLB, LOW);
  digitalWrite(gLC, LOW);
  
  unsigned long int signal=2100000;
  return signal;
}

unsigned long int phase_B()
{
  digitalWrite(gHA, LOW);
  digitalWrite(gHB, HIGH);
  digitalWrite(gHC, LOW);
  digitalWrite(gLA, LOW);
  digitalWrite(gLB, LOW);
  digitalWrite(gLC, LOW);
  
  unsigned long int signal=2010000;
  return signal;
}

unsigned long int phase_C()
{
  digitalWrite(gHA, LOW);
  digitalWrite(gHB, LOW);
  digitalWrite(gHC, HIGH);
  digitalWrite(gLA, LOW);
  digitalWrite(gLB, LOW);
  digitalWrite(gLC, LOW);
  
  unsigned long int signal=2001000;
  return signal;
}
