
#include "printing.h"
#include <stdlib.h>
#include <limits.h>


void print_block(uint32_t block[4], output_format format) {
    printf("\n");
    for (int i = 0; i < 4; i++) {
        const uint32_t current_value = block[i];
        switch (format) {
            case BINARY:
                print_binary_uint32(current_value);
                break;
            case HEX:
                print_hex_uint32(current_value);
                break;
        }
        printf("\n");
    }
    printf("\n");
}

void print_binary_uint8(uint8_t value) {
    for (int i = 7; 0 <= i; i--) {
        printf("%i", (value >> i) & 1);
    }
    printf(" ");
}

void print_binary_uint32(uint32_t value) {
    uint8_t bytes[4];
    bytes[0] = (value >> 24) & 0xFF;
    bytes[1] = (value >> 16) & 0xFF;
    bytes[2] = (value >>  8) & 0xFF;
    bytes[3] =  value        & 0xFF;
    for (int i = 0; i < 4; i++) {
        print_binary_uint8(bytes[i]);
    }
}

void print_hex_uint8(uint8_t value) {
    printf("%02hhX ", value);
}

void print_hex_uint32(uint32_t value) {
    uint8_t bytes[4];
    bytes[0] = (value >> 24) & 0xFF;
    bytes[1] = (value >> 16) & 0xFF;
    bytes[2] = (value >>  8) & 0xFF;
    bytes[3] =  value        & 0xFF;
    for (int i = 0; i < 4; i++) {
        print_hex_uint8(bytes[i]);
    }
}
