//
// serial.c
// based on hello.ftdi.44.echo.c by Neil Gershenfeld
// (then modified beyond recognition)
//

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "serial.h"
#include "macros.h"

volatile char in_buffer[BUFFER_SIZE];
volatile char out_buffer[BUFFER_SIZE];
volatile unsigned int in_buffer_read = 0, in_buffer_write = 0,
                     out_buffer_read = 0, out_buffer_write = 0;
volatile unsigned char line_received = 0;

inline unsigned char in_buffer_full(void)
{
    return in_buffer_write == ((in_buffer_read - 1) & BUFFER_MASK);
}

inline unsigned char out_buffer_full(void)
{
    return out_buffer_write == ((out_buffer_read - 1) & BUFFER_MASK);
}

inline unsigned char in_buffer_empty(void)
{
    return in_buffer_write == in_buffer_read;
}

inline unsigned char out_buffer_empty(void)
{
    return out_buffer_write == out_buffer_read;
}

void serial_init(void)
{
    // Clear transmit complete flag, do not double speed, do not use MPC
    UCSRA = 0b01000010;
    
    // Default frame settings are already correct (8 data bits, 1 stop bit)
    
    // Set baud
    UBRRH = MYUBRR >> 8;
    UBRRL = MYUBRR;
    
    // Turn it on and enable RX interrupt
    // (tx interrupt is enabled when you put a char in the buffer)
    UCSRB = (1 << TXEN) | (1 << RXEN) | (1 << RXCIE);
}

// void get_char(char* c)
//   Gets a character from the buffer and stores it in c.  If no character is
//   available, stores 0 in c.
void get_char(char* c) {
    clear(UCSRB, RXCIE); // Disable rx interrupt
    if (in_buffer_empty())
        *c = 0;
    else
        *c = in_buffer[in_buffer_read++];
    in_buffer_read &= BUFFER_MASK;
    set(UCSRB, RXCIE); // Enable rx interrupt
}

// void put_char(char txchar)
//   Puts a character in the buffer to be output.  If the buffer is full,
//   overwrites the oldest output character (causing it to be skipped in the
//   stream).
void put_char(char txchar) {
    clear(UCSRB, UDRIE); // Disable tx interrupt
    if (out_buffer_full()) // Skip a character
        out_buffer_read = (out_buffer_read + 1) & BUFFER_MASK;
    out_buffer[out_buffer_write++] = txchar;
    out_buffer_write &= BUFFER_MASK;
    set(UCSRB, UDRIE); // Enable tx interrupt
}

// When the output buffer is empty, send the next character in the local
// ring buffer.
ISR(USART_UDRE_vect)
{
    UDR = out_buffer[out_buffer_read++];
    out_buffer_read &= BUFFER_MASK;
    // If we have no more to send, then disable the output buffer.
    if (out_buffer_empty())
        clear(UCSRB, UDRIE); // Disable interrupt
}

// If we get a character, load it into the buffer.
ISR(USART_RX_vect)
{
    if (in_buffer_full()) // Skip a character
        in_buffer_read = (in_buffer_read + 1) & BUFFER_MASK;
    char c = UDR;
    in_buffer[in_buffer_write++] = c;
    if (c == '\n')
        line_received = 1;
    in_buffer_write &= BUFFER_MASK;
}

////////////////////////////////////////////////////////////////////////

void put_bin(unsigned char bin) {
    unsigned char index = 0x80;
    while(index) {
        if (bin & index)
            put_char('1');
        else
            put_char('0');
        index >>= 1;
    }
}

void put_int(int x) {

    if (x == 0) {
        put_char('0');
        return;
    }
      
    
    // Loop until we exceed the value to be printed
    int index = 1;
    for (index = 1; index <= x; index *= 10);
  
    while(index > 1) {
         index /= 10;
         put_char('0' + x / index);
         x = x % index;
    }
}
  
  /*

void put_ram_string(char *str) {
    //
    // print a null-terminated string from SRAM
    //
    static int index;
    index = 0;
    while (str[index] != 0) {
        while(out_buffer_full()); // Loop until there's room in the buffer.
        put_char(str[index++]);
    }
}
   
void put_flash_string(PGM_P str) {
    //
    // print a null-terminated string from flash
    //
    static char chr;
    static int index;
    index = 0;
    
    // If the string is the null string, then return immediately.
    if (!pgm_read_byte(&(str[index])))
        return;
        
    // Otherwise, loop through the values
    do {
        chr = pgm_read_byte(&(str[index]));
        while(out_buffer_full()); // Loop until there's room in the buffer.
        put_char(chr);
        ++index;
    } while (chr != 0);
}
*/