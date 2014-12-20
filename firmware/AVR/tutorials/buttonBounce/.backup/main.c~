#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 1000000UL

int main (void)
{
    //Set LED1
    DDRC |= (1 << PINC5);
    PORTC ^= (1 << PINC5);

    //Set LED2
    DDRB |= (1 << PINB0);

    //Set button
    DDRB &= ~(1 << PINB1);
    PORTB |= (1 << PINB1);

    int prsd=0;
    int prsd_confd=0;
    int reld_confd=0;

    while (1)
    {
        //If button is pressed
        if (bit_is_clear(PINB, 1)) {
            prsd_confd++;
            reld_confd=0;

            //check that button was actually pressed
            if (prsd_confd > 100) {
               if (prsd == 0) {
                    PORTC ^= (1 << PINC5);
                    PORTB ^= (1 << PINB0);
                    prsd=1;
                }
                prsd_confd=0;
            }
        } else {
            reld_confd++;
            prsd_confd=0;

            if (reld_confd > 100) {
                prsd=0;
                reld_confd=0;
            }
        }
    }
}
