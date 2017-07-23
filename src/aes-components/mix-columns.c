
#include "mix-columns.h"
#include <string.h>


aes_byte multiply_by_1(aes_byte value);
aes_byte multiply_by_2(aes_byte value);
aes_byte multiply_by_3(aes_byte value);

typedef aes_byte (*gf8_multiplication)(aes_byte);
const gf8_multiplication gf8_multiplications[AES_BLOCK_MATRIX_SPAN][AES_BLOCK_MATRIX_SPAN] = {
    { multiply_by_2, multiply_by_3, multiply_by_1, multiply_by_1 },
    { multiply_by_1, multiply_by_2, multiply_by_3, multiply_by_1 },
    { multiply_by_1, multiply_by_1, multiply_by_2, multiply_by_3 },
    { multiply_by_3, multiply_by_1, multiply_by_1, multiply_by_2 }
};

void mix_columns(aes_byte block[AES_BLOCK_MATRIX_SPAN][AES_BLOCK_MATRIX_SPAN]) {
    
    aes_byte result[AES_BLOCK_MATRIX_SPAN][AES_BLOCK_MATRIX_SPAN] = {0};
    
    for (int i = 0; i < AES_BLOCK_MATRIX_SPAN; i++) {
        for (int j = 0; j < AES_BLOCK_MATRIX_SPAN; j++) {
            aes_byte temp = 0;
            for (int k = 0; k < AES_BLOCK_MATRIX_SPAN; k++) {
                const gf8_multiplication multiply = gf8_multiplications[j][k];
                const aes_byte multiplier = block[k][i];
                temp ^= multiply(multiplier);
            }
            result[j][i] = temp;
        }
    }
    
    for(int i = 0; i < AES_BLOCK_MATRIX_SPAN; i++) {
        memcpy(&block[i], &result[i], sizeof(result[0]));
    }
}

aes_byte multiply_by_1(aes_byte value) {
    return value;
}

aes_byte multiply_by_2(aes_byte value) {
    if (value < 0b10000000) {
        return value << 1;
    }
    return (value << 1) ^ AES_IRREDUCIBLE_POLYNOMIAL;
}

aes_byte multiply_by_3(aes_byte value) {
    return multiply_by_2(value) ^ value;
}
