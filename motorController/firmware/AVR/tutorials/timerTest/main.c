#include <avr/io.h>

#define F_CPU 1000000UL

#define hA PINB1
#define hB PINB2
#define hC PINB3
#define lA PINB0
#define lB PIND7
#define lC PIND6


int main(void)
{
    int on=0;
    int count=0;
    DDRB = 0b00001111;
    DDRD = 0b11000000;
    PORTB = 0b00000000;
    PORTD = 0b00000000;

    TCCR1B |= (1 << CS10);

    while(1)
    {
        if (TCNT1 > 33333 && on==0) {
            TCNT1 = 0;
            count++;
            if (count == 30) {
                on = 0;
                PORTB &= ~(1 << hB);
                PORTD &= ~(1 << lB);
                PORTB |= (1 << hA);
                PORTB |= (1 << lA);
                count=0;
            } else if (count == 20) {
                PORTB &= ~(1 << hC);
                PORTD &= ~(1 << lC);
                PORTD |= (1 << lB);
                PORTB |= (1 << hB);
            } else if (count == 10) {
                PORTB &= ~(1 << hA);
                PORTB &= ~(1 << lA);
                PORTD |= (1 << lC);
                PORTB |= (1 << hC);
            }
        }
    }
}
