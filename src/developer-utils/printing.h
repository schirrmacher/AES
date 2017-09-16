
#ifndef printing_h
#define printing_h

#include <stdio.h>

typedef enum { BINARY, HEX } output_format;

void print_block(uint32_t block[4], output_format format);

void print_binary_uint8(uint8_t value);
void print_binary_uint32(uint32_t value);

void print_hex_uint8(uint8_t value);
void print_hex_uint32(uint32_t value);

#endif /* printing_h */
