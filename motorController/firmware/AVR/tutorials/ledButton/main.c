#include <avr/io.h>

#define F_CPU 1000000UL

int main (void)
{
    DDRC |= 1 << PINC5; //set PORTC-PIN5 as output
    PORTC &= ~(1<<PINC5);
    DDRB &= ~(1 << PINB1); //set PORTB-PIN1 as input
    PORTB |= (1<<PINB1);

    //while (1)
    //{
    //  PORTC ^= 1 << PINC5;
    //  if (bit_is_clear(PINB, 1)) {
    //    _delay_ms(60);
    //  } else {
    //    _delay_ms(200);
    //  }
    //}

    while (1)
    {
        if (bit_is_clear(PINB, 1)) {
            PORTC |= (1<<PINC5);
        } else {
            PORTC &= ~(1<<PINC5);
        }

    }
}

