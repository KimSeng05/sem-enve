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
  //signal 100001
  //Write high signals
  analogWrite(gHA, 255);
  analogWrite(gLC, 255);

  //Write all other outputs to null;
  analogWrite(gHB, 0);
  analogWrite(gHC, 0);
  analogWrite(gLA, 0);
  analogWrite(gLB, 0);
  readA=5*analogRead(A_IN)/1024;
  readB=5*analogRead(B_IN)/1024;
  readC=5*analogRead(C_IN)/1024;

  //print Output
  lcd.setCursor(0,0);
  lcd.print(readA,1);
  lcd.setCursor(0,1);
  lcd.print(readB,1);
  lcd.print(" ");
  lcd.print(readC,1);

  //Allow user to read
  delay(1*1000);

  //clear screen
  lcd.clear();
}
