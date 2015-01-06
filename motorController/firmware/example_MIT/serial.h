// Originally by
// Neil Gershenfeld
// 12/8/10
//
// Modified beyond recognition by Matt Keeter
//

#ifndef SERIAL_H
#define SERIAL_H

#define BUFFER_SIZE 32 // must be a power of 2, otherwise the
#define BUFFER_MASK (BUFFER_SIZE - 1) // masking won't work.

#include <avr/pgmspace.h>

#define BAUD 4800
#define MYUBRR (((((F_CPU * 10) / (16L * BAUD)) + 5) / 10) - 1)

void serial_init(void);
void get_char(char *rxbyte);
void put_char(char txchar);
void put_bin(unsigned char bin);
void put_int(int i);
void put_ram_string(char *str);
void put_flash_string(PGM_P str);

// Buffer related functions
inline unsigned char out_buffer_full(void);
inline unsigned char in_buffer_full(void);
inline unsigned char out_buffer_empty(void);
inline unsigned char in_buffer_empty(void);

extern volatile unsigned char line_received;
#endif