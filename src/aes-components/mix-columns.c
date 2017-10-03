
#include "mix-columns.h"
#include <string.h>


static byte multiply_by_01(byte value);
static byte multiply_by_02(byte value);
static byte multiply_by_03(byte value);

static byte multiply_by_09(byte value);
static byte multiply_by_11(byte value);
static byte multiply_by_13(byte value);
static byte multiply_by_14(byte value);

typedef byte (*gf8_multiplication)(byte);

static const gf8_multiplication gf8_multiplications[AES_STATE_SPAN][AES_STATE_SPAN] = {
    multiply_by_02, multiply_by_03, multiply_by_01, multiply_by_01,
    multiply_by_01, multiply_by_02, multiply_by_03, multiply_by_01,
    multiply_by_01, multiply_by_01, multiply_by_02, multiply_by_03,
    multiply_by_03, multiply_by_01, multiply_by_01, multiply_by_02
};

static const gf8_multiplication inv_gf8_multiplications[AES_STATE_SPAN][AES_STATE_SPAN] = {
    multiply_by_14, multiply_by_11, multiply_by_13, multiply_by_09,
    multiply_by_09, multiply_by_14, multiply_by_11, multiply_by_13,
    multiply_by_13, multiply_by_09, multiply_by_14, multiply_by_11,
    multiply_by_11, multiply_by_13, multiply_by_09, multiply_by_14
};

static byte multiply_by_01(byte value) {
    return value;
}

static byte multiply_by_02(byte value) {
    if (value < 0b10000000) {
        return value << 1;
    }
    return (value << 1) ^ AES_IRREDUCIBLE_POLYNOMIAL;
}

static byte multiply_by_03(byte value) {
    return multiply_by_02(value) ^ value;
}

// (((x×2)×2)×2)+x
static byte multiply_by_09(byte value) {
    return multiply_by_02(multiply_by_02(multiply_by_02(value))) ^ value;
}

// ((((x×2)×2)+x)×2)+x
static byte multiply_by_11(byte value) {
    return multiply_by_02(multiply_by_02(multiply_by_02(value)) ^ value) ^ value;
}

// ((((x×2)+x)×2)×2)+x
static byte multiply_by_13(byte value) {
    return multiply_by_02(multiply_by_02(multiply_by_02(value) ^ value)) ^ value;
}

// ((((x×2)+x)×2)+x)×2
static byte multiply_by_14(byte value) {
    return multiply_by_02(multiply_by_02(multiply_by_02(value) ^ value) ^ value);
}

void mix_columns(state state_ref) {
    
    byte result[AES_STATE_SPAN][AES_STATE_SPAN];
    
    for (int i = 0; i < AES_STATE_SPAN; i++) {
        for (int j = 0; j < AES_STATE_SPAN; j++) {
            
            byte result_value = 0;
            
            for (int k = 0; k < AES_STATE_SPAN; k++) {
                const gf8_multiplication multiply_operation = gf8_multiplications[j][k];
                const byte multiplier = state_ref[k][i];
                result_value ^= multiply_operation(multiplier);
            }
            
            result[j][i] = result_value;
        }
    }
    
    memcpy(state_ref, result, sizeof(byte) * AES_STATE_SPAN * AES_STATE_SPAN);
}

void inv_mix_columns(state state_ref) {
    
    byte result[AES_STATE_SPAN][AES_STATE_SPAN];
    
    for (int i = 0; i < AES_STATE_SPAN; i++) {
        for (int j = 0; j < AES_STATE_SPAN; j++) {
            
            byte result_value = 0;
            
            for (int k = 0; k < AES_STATE_SPAN; k++) {
                const gf8_multiplication multiply_operation = inv_gf8_multiplications[j][k];
                const byte multiplier = state_ref[k][i];
                result_value ^= multiply_operation(multiplier);
            }
            
            result[j][i] = result_value;
        }
    }
    
    memcpy(state_ref, result, sizeof(byte) * AES_STATE_SPAN * AES_STATE_SPAN);
}
