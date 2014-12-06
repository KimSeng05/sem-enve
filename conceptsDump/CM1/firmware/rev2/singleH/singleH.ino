#include <LiquidCrystal.h>

#define checkLED 2

//define Gate Input pins
#define mH A3
#define mL A4

LiquidCrystal lcd(4,5,6,7,8,9);
int lastRun=0;
//char inSignal[3];

void setup()
{
  //debugging 
  lcd.begin(16,2);
  pinMode(checkLED, OUTPUT);
  
  pinMode(mH, OUTPUT);
  pinMode(mL, OUTPUT);
}

void loop()
{
  //Activate checkLED
  digitalWrite(checkLED, LOW);
  delay(0.5*1000);
  digitalWrite(checkLED, HIGH);
  
//  if (lastRun==0) {
//    digitalWrite(mH, HIGH);
//    digitalWrite(mL, HIGH);
//    inSignal[0]='1';
//    inSignal[1]='1';
//    inSignal[2]='\0';
//    lastRun=1;
//  } else if (lastRun==1) {
//    digitalWrite(mH, LOW);
//    digitalWrite(mL, LOW);
//    inSignal[0]='0';
//    inSignal[1]='0';
//    inSignal[2]='\0';
//    lastRun=0;
//  } else {
//    lastRun=1;
//  }
  
  //print to LCD
  lcd.setCursor(0,0);
  digitalWrite(mH, HIGH);
  digitalWrite(mL, HIGH);
  lcd.print("Test H-Bridge ");
  //lcd.print(inSignal);
  lcd.print("11");
  lcd.setCursor(0,1);
  lcd.print("t");
  lcd.print(millis()/1000);
  
  delay(1*1000);
  lcd.clear();
}
