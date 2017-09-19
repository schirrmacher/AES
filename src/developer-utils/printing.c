
#include "printing.h"
#include <stdlib.h>
#include <limits.h>


void print_state(uint8_t state[4][4]) {
    printf("\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            const uint8_t current_value = state[i][j];
            print_hex_uint8(current_value);
        }
        printf("\n");
    }
    printf("\n");
}

void print_hex_uint8(uint8_t value) {
    printf("%02hhX ", value);
}
