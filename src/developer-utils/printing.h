
#ifndef printing_h
#define printing_h

#include <stdio.h>
#include <stdint.h>

typedef enum { BINARY, HEX } output_format;

void print_state(uint32_t state[4], output_format format);

void print_binary_uint8(uint8_t value);
void print_binary_uint32(uint32_t value);

void print_hex_uint8(uint8_t value);
void print_hex_uint32(uint32_t value);

#endif /* printing_h */
