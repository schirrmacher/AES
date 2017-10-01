
#include "mix-columns.h"
#include <string.h>


static byte multiply_by_1(byte value);
static byte multiply_by_2(byte value);
static byte multiply_by_3(byte value);

typedef byte (*gf8_multiplication)(byte);

static const gf8_multiplication gf8_multiplications[AES_STATE_SPAN][AES_STATE_SPAN] = {
    multiply_by_2, multiply_by_3, multiply_by_1, multiply_by_1,
    multiply_by_1, multiply_by_2, multiply_by_3, multiply_by_1,
    multiply_by_1, multiply_by_1, multiply_by_2, multiply_by_3,
    multiply_by_3, multiply_by_1, multiply_by_1, multiply_by_2
};

void mix_columns(state state) {
    
    byte result[AES_STATE_SPAN][AES_STATE_SPAN];
    
    for (int i = 0; i < AES_STATE_SPAN; i++) {
        for (int j = 0; j < AES_STATE_SPAN; j++) {
            
            byte result_value = 0;
            
            for (int k = 0; k < AES_STATE_SPAN; k++) {
                const gf8_multiplication multiply_operation = gf8_multiplications[j][k];
                const byte multiplier = state[k][i];
                result_value ^= multiply_operation(multiplier);
            }
            
            result[j][i] = result_value;
        }
    }
    
    memcpy(state, result, sizeof(byte) * AES_STATE_SPAN * AES_STATE_SPAN);
}

static byte multiply_by_1(byte value) {
    return value;
}

static byte multiply_by_2(byte value) {
    if (value < 0b10000000) {
        return value << 1;
    }
    return (value << 1) ^ AES_IRREDUCIBLE_POLYNOMIAL;
}

static byte multiply_by_3(byte value) {
    return multiply_by_2(value) ^ value;
}
