
#include "printing.h"
#include <stdlib.h>
#include <limits.h>


void print_block(unsigned int rows_count, unsigned int columns_count, unsigned char block[rows_count][columns_count], output_format format) {
    printf("\n");
    for (int row_index = 0; row_index < rows_count; row_index++) {
        for (int column_index = 0; column_index < columns_count; column_index++) {
            const unsigned char current_value = block[row_index][column_index];
            switch (format) {
                case BINARY:
                    print_binary(current_value);
                    break;
                case HEX:
                    print_hex_uint8(current_value);
                    break;
            }
        }
        printf("\n");
    }
    printf("\n");
}

void print_binary(uint8_t value) {
    for (int i = 7; 0 <= i; i--) {
        printf("%i", (value >> i) & 1);
    }
    printf(" ");
}

void print_hex_uint8(uint8_t value) {
    printf("%02hhX ", value);
}

void print_hex_uint32(uint32_t value) {
    uint8_t bytes[4];
    bytes[0] = (value >> 24) & 0xFF;
    bytes[1] = (value >> 16) & 0xFF;
    bytes[2] = (value >> 8) & 0xFF;
    bytes[3] = value & 0xFF;
    for (int i = 0; i < 4; i++) {
        print_hex_uint8(bytes[i]);
    }
}
