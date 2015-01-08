#include <avr/io.h>
#include <util/delay.h>

//#define F_CPU 16000000
//==============================================================================
/*
## Research So Far...

### Resolution
Determines the number of intervals an analogue signal has to *fill*. A 0-5V signal will be mapped to 0 - (2<sup>N</sup>-1) by the ADC for a N-bit resolution.

### Prescalers

A prescaler of N implies F_ADC = F_CPU/N. In general, the ADC operates within a frequency range of 50kHz to 200kHz, which is much smaller than the clock speed of the AVR (MHz) - hence the need for a prescaler.

*Note:* The uncertainty principle applies for frequency and accuracy.

### Registers

- *ADMUX:* ADC Multiplier Selection Register
- *ADCSRA:* ADC Control and Status Register A
- *ADCL* and *ADCH:* ADC Data Registers
- *SFIOR:* Special Function IO Register
*/
//==============================================================================

void adc_init(void)
{
    ADMUX |= (1<<REFS0); //set voltage reference to AVCC (5V);
    //ADMUX |= 0b00000101; //set ADC5
    ADMUX |= (1<<ADLAR);

    ADCSRA |= (1<<ADEN); //Enable ADC
    //ADCSRA |= (1<<ADATE); //Auto Trigger
    ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); //set prescale to 16
}

uint16_t adc_read (void)
{
    //ch &= 0b00000111; //ensure within in bounds 0-7
    //ADMUX |= (ADMUX & 0xF8) | ch; //clears the bottom 3 bits before ORing
    ADMUX |= (1<<MUX2) | (1<<MUX0);
    ADMUX &= ~(1<<MUX1);
    ADMUX &= ~(1<<MUX3);

    //Start single conversion
    ADCSRA |= (1<<ADSC);

    //wait for conversion to complete
    //while(ADCSRA & (1<<ADSC)){
    //}
    loop_until_bit_is_set(ADCSRA, ADSC);

    //return (ADCH<<2|ADCL>>6);
    return (ADC);
}


void pwm_init(void)
{
    DDRB |= (1<<PB1);
    TCCR1A |= (1<<WGM11) | (1<<COM1A1) | (1<<COM1A0);
    TCCR1B |= (1<<WGM12) | (1<<WGM13) | (1<<CS10);
    ICR1=40000;
}

int main (void)
{
    adc_init();
    pwm_init();

    while (1)
    {
        //for (int i=0; i<1024; i++){
        //    OCR1A = 1024 - i;
        //    _delay_ms(10);
        //}
        OCR1A = ICR1 - adc_read();
        //OCR1A = ICR1 - 10000;
    }
}
