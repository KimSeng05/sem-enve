#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "hbridge.h"
#include "macros.h"

static int discharge_delay = 20;

void hbridge_init(void)
{
    pinA_low();
    pinB_low();
    pinC_low();
    pinD_low();
}

/*
Pin A:
High    pd5
Low     pd4
*/

inline void pinA_off(void)
{
    clear(PORTD, PD5);
    clear(PORTD, PD4);
    clear(DDRD, PD5);
    clear(DDRD, PD4);
}

inline void pinA_high(void)
{  
    clear(PORTD, PD4);
    _delay_us(discharge_delay);
    set(PORTD, PD5);
    
    set(DDRD, PD5);
    set(DDRD, PD4);
}

inline void pinA_low(void)
{
    clear(PORTD, PD5);
    _delay_us(discharge_delay);
    set(PORTD, PD4);
    
    set(DDRD, PD5);
    set(DDRD, PD4);
}

/*
Pin B:
High    pd2
Low     pd3
*/
inline void pinB_off(void)
{
    clear(DDRD, PD2);
    clear(DDRD, PD3);
    
    clear(PORTD, PD2);
    clear(PORTD, PD3);
}

inline void pinB_high(void)
{   
    clear(PORTD, PD3);
    _delay_us(discharge_delay);
    set(PORTD, PD2);

    
    set(DDRD, PD2);
    set(DDRD, PD3);
}

inline void pinB_low(void)
{
    clear(PORTD, PD2);
    _delay_us(discharge_delay);
    set(PORTD, PD3);
    
    set(DDRD, PD2);
    set(DDRD, PD3);
}

/*
Pin C:
High    pb4
Low     pb3
*/
inline void pinC_off(void)
{
    clear(DDRB, PB3);
    clear(DDRB, PB4);
    
    clear(PORTB, PB4);
    clear(PORTB, PB3);
}

inline void pinC_high(void)
{   
    clear(PORTB, PB3);
    _delay_us(discharge_delay);
    set(PORTB, PB4);
    
    set(DDRB, PB3);
    set(DDRB, PB4);
}

inline void pinC_low(void)
{
    clear(PORTB, PB4);
    _delay_us(discharge_delay);
    set(PORTB, PB3);
    
    set(DDRB, PB3);
    set(DDRB, PB4);
}

/*
Pin D:
High    pb0
Low     pd6
*/
inline void pinD_off(void)
{
    clear(DDRD, PD6);
    clear(DDRB, PB0);
    
    clear(PORTD, PD6);
    clear(PORTB, PB0);
}

inline void pinD_high(void)
{   
    clear(PORTD, PD6);
    _delay_us(discharge_delay);
    set(PORTB, PB0);
    
    set(DDRB, PB0);
    set(DDRD, PD6);
}

inline void pinD_low(void)
{
    clear(PORTB, PB0);
    _delay_us(discharge_delay);
    set(PORTD, PD6);
    
    set(DDRB, PB0);
    set(DDRD, PD6);
}