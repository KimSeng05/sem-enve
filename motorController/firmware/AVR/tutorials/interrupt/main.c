#include <avr/io.h>
#include <avr/interrupt.h>

int main (void)
{
    sei();
    DDRB = 0b00000001;
    DDRD = 0b00000000;
    PORTD |= (1<<PIND2);
    EICRA &= ~(1<<ISC01);
    EICRA |= (1<<ISC00);
    EIMSK |= (1<<INT0);

    while (1)
    {
    }
}

//interrupt service routine
ISR (INT0_vect)
{
    PORTB ^= (1<<PB0);
}
