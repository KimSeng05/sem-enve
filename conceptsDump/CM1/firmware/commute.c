#include <LiquidCrystal.h>

//define PWM pins
#define gHA 11
#define gLA 10
#define gHB 9
#define gLB 6
#define gLC 5
#define gHC 3

//define AnalogInputs
#define A_IN A0
#define B_IN A1
#define C_IN A2

//Initilize LCD display
LiquidCrystal lcd(0,1,2,4,7,8);

//Initalize Read-in values
float readA=0.0;
float readB=0.0;
float readC=0.0;

int lastRun=0;

void setup()
{
  lcd.begin(16,2);

  //Set PWM pins to OUTPUT
  pinMode(gHA, OUTPUT);
  pinMode(gHB, OUTPUT);
  pinMode(gHC, OUTPUT);
  pinMode(gLA, OUTPUT);
  pinMode(gLB, OUTPUT);
  pinMode(gLC, OUTPUT);

  //Set read pins to INPUT
  pinMode(A_IN, INPUT);
  pinMode(B_IN, INPUT);
  pinMode(C_IN, INPUT);
}

void loop()
{
  //Write NULL to all signals
  analogWrite(gHA, 0);
  analogWrite(gHB, 0);
  analogWrite(gHC, 0);
  analogWrite(gLA, 0);
  analogWrite(gLB, 0);
  analogWrite(gLC, 0);

  //Read Hall signals
  readA=analogRead(A_IN)*100/1024;
  readB=analogRead(B_IN)*100/1024;
  readC=analogRead(C_IN)*100/1024;

  //print Output
  lcd.setCursor(0,0);
  lcd.print(readA,1);
  lcd.print(" ");
  lcd.print(readB,1);
  lcd.print(" ");
  lcd.print(readC,1);
  lcd.setCursor(0,1);

  if (lastRun == 1) {
    lcd.print(A-B);
    analogWrite(gHA, 255);
    analogWrite(gHB, 0);
    analogWrite(gHC, 0);
    analogWrite(gLA, 0);
    analogWrite(gLB, 255);
    analogWrite(gLC, 0);
    lastRun=5;
  } else if (lastRun == 5) {
    lcd.print(A-C)
    analogWrite(gHA, 255);
    analogWrite(gHB, 0);
    analogWrite(gHC, 0);
    analogWrite(gLA, 0);
    analogWrite(gLB, 0);
    analogWrite(gLC, 255);
    lastRun=4;
  } else if (lastRun == 4) {
    lcd.print(B-C);
    analogWrite(gHA, 0);
    analogWrite(gHB, 255);
    analogWrite(gHC, 0);
    analogWrite(gLA, 0);
    analogWrite(gLB, 0);
    analogWrite(gLC, 255);
    lastRun=6;
  } else if (lastRun == 6) {
    lcd.print(B-A);
    analogWrite(gHA, 0);
    analogWrite(gHB, 255);
    analogWrite(gHC, 0);
    analogWrite(gLA, 255);
    analogWrite(gLB, 0);
    analogWrite(gLC, 0);
    lastRun=2;
  } else if (lastRun == 2) {
    lcd.print(C-A);
    analogWrite(gHA, 0);
    analogWrite(gHB, 0);
    analogWrite(gHC, 255);
    analogWrite(gLA, 255);
    analogWrite(gLB, 0);
    analogWrite(gLC, 0);
    lastRun=3;
  } else if (lastRun == 1) {
    lcd.print(C-B);
    analogWrite(gHA, 0);
    analogWrite(gHB, 0);
    analogWrite(gHC, 255);
    analogWrite(gLA, 0);
    analogWrite(gLB, 255);
    analogWrite(gLC, 0);
    lastRun=1;
  } else {
    lastRun = 0;
  }

  //clear screen
  lcd.clear();

}
