#include <avr/io.h>
#include <avr/delay.h>

int main (void)
{
  //Change PORT C Pin 5 to output
  DDRC = 0b00100000;

  //assigning 5v to pin 5
  PORTC = 0b00100000;

  while (1) {}

  return 0;
}
