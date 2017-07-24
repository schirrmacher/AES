
#include "mix-columns.h"
#include <string.h>


uint8_t multiply_by_1(uint8_t value);
uint8_t multiply_by_2(uint8_t value);
uint8_t multiply_by_3(uint8_t value);

typedef uint8_t (*gf8_multiplication)(uint8_t);
const gf8_multiplication gf8_multiplications[AES_BLOCK_MATRIX_SPAN][AES_BLOCK_MATRIX_SPAN] = {
    multiply_by_2, multiply_by_3, multiply_by_1, multiply_by_1,
    multiply_by_1, multiply_by_2, multiply_by_3, multiply_by_1,
    multiply_by_1, multiply_by_1, multiply_by_2, multiply_by_3,
    multiply_by_3, multiply_by_1, multiply_by_1, multiply_by_2
};

void mix_columns(uint8_t block[AES_BLOCK_MATRIX_SPAN][AES_BLOCK_MATRIX_SPAN]) {
    
    uint8_t result[AES_BLOCK_MATRIX_SPAN][AES_BLOCK_MATRIX_SPAN];
    
    for (int i = 0; i < AES_BLOCK_MATRIX_SPAN; i++) {
        for (int j = 0; j < AES_BLOCK_MATRIX_SPAN; j++) {
            uint8_t temp = 0;
            for (int k = 0; k < AES_BLOCK_MATRIX_SPAN; k++) {
                const gf8_multiplication multiply = gf8_multiplications[j][k];
                const uint8_t multiplier = block[k][i];
                temp ^= multiply(multiplier);
            }
            result[j][i] = temp;
        }
    }
    
    for(int i = 0; i < AES_BLOCK_MATRIX_SPAN; i++) {
        memcpy(&block[i], &result[i], sizeof(result[0]));
    }
}

uint8_t multiply_by_1(uint8_t value) {
    return value;
}

uint8_t multiply_by_2(uint8_t value) {
    if (value < 0b10000000) {
        return value << 1;
    }
    return (value << 1) ^ AES_IRREDUCIBLE_POLYNOMIAL;
}

uint8_t multiply_by_3(uint8_t value) {
    return multiply_by_2(value) ^ value;
}
