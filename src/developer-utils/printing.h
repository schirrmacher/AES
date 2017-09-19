
#ifndef printing_h
#define printing_h

#include <stdio.h>
#include <stdint.h>

void print_state(uint8_t state[4][4]);

void print_hex_uint8(uint8_t value);
void print_hex_uint32(uint32_t value);

#endif /* printing_h */
