
#include "mix-columns.h"
#include <string.h>


static uint8_t multiply_by_1(uint8_t value);
static uint8_t multiply_by_2(uint8_t value);
static uint8_t multiply_by_3(uint8_t value);

typedef uint8_t (*gf8_multiplication)(uint8_t);

static const gf8_multiplication gf8_multiplications[AES_STATE_MATRIX_SPAN][AES_STATE_MATRIX_SPAN] = {
    multiply_by_2, multiply_by_3, multiply_by_1, multiply_by_1,
    multiply_by_1, multiply_by_2, multiply_by_3, multiply_by_1,
    multiply_by_1, multiply_by_1, multiply_by_2, multiply_by_3,
    multiply_by_3, multiply_by_1, multiply_by_1, multiply_by_2
};

void mix_columns(uint8_t state[AES_KEY_WORDS][AES_WORD_BYTES]) {
    
    uint8_t result[AES_STATE_MATRIX_SPAN][AES_STATE_MATRIX_SPAN];
    
    for (int i = 0; i < AES_STATE_MATRIX_SPAN; i++) {
        for (int j = 0; j < AES_STATE_MATRIX_SPAN; j++) {
            
            uint8_t result_value = 0;
            
            for (int k = 0; k < AES_STATE_MATRIX_SPAN; k++) {
                const gf8_multiplication multiply_operation = gf8_multiplications[j][k];
                const uint8_t multiplier = state[k][i];
                result_value ^= multiply_operation(multiplier);
            }
            
            result[j][i] = result_value;
        }
    }
    
    memcpy(state, result, sizeof(uint8_t) * AES_STATE_MATRIX_SPAN * AES_STATE_MATRIX_SPAN);
}

static uint8_t multiply_by_1(uint8_t value) {
    return value;
}

static uint8_t multiply_by_2(uint8_t value) {
    if (value < 0b10000000) {
        return value << 1;
    }
    return (value << 1) ^ AES_IRREDUCIBLE_POLYNOMIAL;
}

static uint8_t multiply_by_3(uint8_t value) {
    return multiply_by_2(value) ^ value;
}
