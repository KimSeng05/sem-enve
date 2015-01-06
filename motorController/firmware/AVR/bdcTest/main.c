#include <avr/io.h>
#include <avr/interrupt.h>

int main (void)
{
    sei();//Enable Global Interrupts
    DDRB = 0b00000010; //Set PINB1 as output
    DDRD = 0b00000000; //Set PIND0 as input
    PORTD |= (1<<PIND2); //enable internal pull-up resistor
    EICRA &= ~(1<<ISC01);
    EICRA |= (1<<ISC00);
    EIMSK |= (1<<INT0);

	while (1) {
	}
}

ISR (INT0_vect)
{
    PORTB ^= (1<<PB1);
}
//button to change direction
//Potentiometer to change speed
//Emergency stop switch
