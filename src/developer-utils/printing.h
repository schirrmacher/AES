
#ifndef printing_h
#define printing_h

#include <stdio.h>

typedef enum { BINARY, HEX } output_format;

void print_block(unsigned int rows_count, unsigned int columns_count, uint8_t block[rows_count][columns_count], output_format format);

void print_binary(uint8_t value);
void print_hex(uint8_t value);

#endif /* printing_h */
