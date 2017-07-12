
#ifndef printing_h
#define printing_h

#include <stdio.h>

typedef enum { BINARY, HEX } output_format;

void print_matrix(unsigned int rows_count, unsigned int columns_count, unsigned char matrix[rows_count][columns_count], output_format format);

#endif /* printing_h */
