
#include "mix-columns.h"
#include <string.h>


unsigned char multiply_by_1(unsigned char value);
unsigned char multiply_by_2(unsigned char value);
unsigned char multiply_by_3(unsigned char value);

typedef unsigned char (*GF8Multiplication)(unsigned char);
const GF8Multiplication gf8Multiplications[AES_MATRIX_SPAN][AES_MATRIX_SPAN] = {
    { multiply_by_2, multiply_by_3, multiply_by_1, multiply_by_1 },
    { multiply_by_1, multiply_by_2, multiply_by_3, multiply_by_1 },
    { multiply_by_1, multiply_by_1, multiply_by_2, multiply_by_3 },
    { multiply_by_3, multiply_by_1, multiply_by_1, multiply_by_2 }
};

void mix_columns(unsigned char matrix[AES_MATRIX_SPAN][AES_MATRIX_SPAN]) {
    
    unsigned char result[AES_MATRIX_SPAN][AES_MATRIX_SPAN] = {0};
    
    for (int i = 0; i < AES_MATRIX_SPAN; i++) {
        for (int j = 0; j < AES_MATRIX_SPAN; j++) {
            unsigned char temp = 0;
            for (int k = 0; k < AES_MATRIX_SPAN; k++) {
                const GF8Multiplication multiply = gf8Multiplications[j][k];
                const unsigned char multiplier = matrix[k][i];
                temp ^= multiply(multiplier);
            }
            result[j][i] = temp;
        }
    }
    
    for(int i = 0; i < AES_MATRIX_SPAN; i++) {
        memcpy(&matrix[i], &result[i], sizeof(result[0]));
    }
}

unsigned char multiply_by_1(unsigned char value) {
    return value;
}

unsigned char multiply_by_2(unsigned char value) {
    if (value < 0b10000000) {
        return value << 1;
    }
    return (value << 1) ^ AES_IRREDUCIBLE_POLYNOMIAL;
}

unsigned char multiply_by_3(unsigned char value) {
    return multiply_by_2(value) ^ value;
}
