#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 1000000UL

int main (void)
{
  //Change PORT C Pin 5 to output
  DDRC |= 1 << PINC5;

  while (1) {
    PORTC ^= 1 << PINC5;
    _delay_ms(100);
  }
}
