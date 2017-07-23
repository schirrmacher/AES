
#include "printing.h"
#include <stdlib.h>
#include <limits.h>


void binary_representation(unsigned char value);

void print_matrix(unsigned int rows_count, unsigned int columns_count, unsigned char matrix[rows_count][columns_count], output_format format) {
    printf("\n");
    for (int row_index = 0; row_index < rows_count; row_index++) {
        for (int column_index = 0; column_index < columns_count; column_index++) {
            const unsigned char current_value = matrix[row_index][column_index];
            switch (format) {
                case BINARY:
                    print_binary(current_value);
                    break;
                case HEX:
                    print_hex(current_value);
                    break;
            }
        }
        printf("\n");
    }
    printf("\n");
}

void print_binary(unsigned char value) {
    for (int i = 7; 0 <= i; i--) {
        printf("%i", (value >> i) & 1);
    }
    printf(" ");
}

void print_hex(unsigned char value) {
    printf("%02hhX ", value);
}
