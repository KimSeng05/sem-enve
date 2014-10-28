#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "serial.h"
#include "macros.h"
#include "hbridge.h"

#define STEP_SIZE 10

void spin_at(unsigned int delay_time)
{
    pinA_high();
    pinB_off();
    pinD_low();
    _delay_loop_2(delay_time);
    
    pinA_off();
    pinB_high();
    pinD_low();
    _delay_loop_2(delay_time);
    
    pinA_low();
    pinB_high();
    pinD_off();
    _delay_loop_2(delay_time);
    
    pinA_low();
    pinB_off();
    pinD_high();
    _delay_loop_2(delay_time);
    
    pinA_off();
    pinB_low();
    pinD_high();
    _delay_loop_2(delay_time);
    
    pinA_high();
    pinB_low();
    pinD_off();
    _delay_loop_2(delay_time);
}

// One sixth of a turn
void spin_smooth(unsigned int delay_time)
{
    pinA_high();
    pinB_off();
    pinD_low();
    _delay_loop_2(delay_time);

        pinA_high();
        pinB_high();
        pinD_low();
        _delay_loop_2(delay_time);
    
    pinA_off();
    pinB_high();
    pinD_low();
    _delay_loop_2(delay_time);

        pinA_low();
        pinB_high();
        pinD_low();
        _delay_loop_2(delay_time);
    
    pinA_low();
    pinB_high();
    pinD_off();
    _delay_loop_2(delay_time);

        pinA_low();
        pinB_high();
        pinD_high();
        _delay_loop_2(delay_time);

    pinA_low();
    pinB_off();
    pinD_high();
    _delay_loop_2(delay_time);

        pinA_low();
        pinB_low();
        pinD_high();
        _delay_loop_2(delay_time);
    
    pinA_off();
    pinB_low();
    pinD_high();
    _delay_loop_2(delay_time);

        pinA_high();
        pinB_low();
        pinD_high();
        _delay_loop_2(delay_time);

    pinA_high();
    pinB_low();
    pinD_off();
    _delay_loop_2(delay_time);

        pinA_high();
        pinB_low();
        pinD_low();
        _delay_loop_2(delay_time);

}

int main(void)
{
    //
    // main
    //
    
    // Initialize various special features
    serial_init();
    hbridge_init();
    
    // Enable global interrupts (for serial communication)
    sei();
    
    //put_char('s');
//    put_char('\n');
  //  _delay_ms(5);
    
    // A-high, B-off, D-low
    // A-off, B-high, D-low
    // A-low, B-high, D-off
    // A-low, B-off, D-high
    // A-off, B-low, D-high
    // A-high, B-low, D-off
    
//    static const unsigned char spin[] = {0b110001, 0b001101, 0b011100, 0b010011, 0b000111, 0b110100};

    volatile int set_point = 3000;
    volatile int delay_time = set_point;
    unsigned char running = 0;
    unsigned int i = 0;
        
    while(1) {
        if (running)
            spin_smooth(delay_time);
        else {
            pinA_low();
            pinB_low();
            pinC_low();
            _delay_ms(100);
        }
        
        // Command format: any number is interpeted as a delay time
        // and starts the system running.
        // A 'j' anywhere in the string commands the system to jump to
        // the given time (rather than gradually changing speed)
        // An 's' in the string commands the system to stop running.
        if (line_received) {
            line_received = 0;
            int new_set_point = 0;
            unsigned char jump = 0;
            unsigned char stop = 0;

            // Parse this line of input
            while(!in_buffer_empty()) {
                char c;
                get_char(&c);
                if (c >= '0' && c <= '9') {
                    running = 1;
                    new_set_point = new_set_point * 10 + c - '0';
                } else if (c == 's')
                    stop = 1;
                else if (c == 'j')
                    jump = 1;
            }
            if (new_set_point < 500)
                new_set_point = 500;
            if (new_set_point > 3000)
                new_set_point = 3000;

            if (stop)
                running = 0;
            if (running)
                set_point = new_set_point;            
            if (jump)
                delay_time = set_point;

        }
        
        
        if (delay_time < (set_point - STEP_SIZE))
            delay_time += STEP_SIZE;
        else if (delay_time < set_point)
            delay_time++;

        if (delay_time > set_point + STEP_SIZE)
            delay_time -= STEP_SIZE;
        else if (delay_time > set_point)
            delay_time--;
        
        // Output speed every eighth tick
        if (!(i++ % 8)) {
            put_int(delay_time);
            put_char('\n');
        }
    }

	return 0;
}