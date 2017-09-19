
#include <stdio.h>
#include "./developer-utils/printing.h"
#include "./aes-components/aes-constants.h"
#include "./aes-components/substitute.h"
#include "./aes-components/shift-rows.h"
#include "./aes-components/mix-columns.h"
#include "./aes-components/key-addition.h"
#include <string.h>
#include <assert.h>

#include "printing.h"

int main(int argc, const char * argv[]) {
    
    uint32_t input_key[4] = {
        0x2b7e1516, 0x28aed2a6, 0xabf71588, 0x09cf4f3c
    };
    
    uint32_t plaintext[4] = {
        0x6bc1bee2, 0x2e409f96, 0xe93d7e11, 0x7393172a
    };
    
    uint8_t key[4][4];
    for (int i = 0; i < AES_STATE_MATRIX_SPAN; i++) {
        key[0][i] = (input_key[i] >> 24) & 0xFF;
        key[1][i] = (input_key[i] >> 16) & 0xFF;
        key[2][i] = (input_key[i] >>  8) & 0xFF;
        key[3][i] =  input_key[i]        & 0xFF;
    }
    
    uint8_t state[4][4];
    for (int i = 0; i < AES_STATE_MATRIX_SPAN; i++) {
        state[0][i] = (plaintext[i] >> 24) & 0xFF;
        state[1][i] = (plaintext[i] >> 16) & 0xFF;
        state[2][i] = (plaintext[i] >>  8) & 0xFF;
        state[3][i] =  plaintext[i]        & 0xFF;
    }
    
    add_round_key(state, key);
    
    for (int i = 1; i <= 9; i++) {
        substitute(state);
        shift_rows(state);
        mix_columns(state);
        add_round_key(state, key);
    }
    
    substitute(state);
    shift_rows(state);
    add_round_key(state, key);
    
    uint32_t result[4] = {
        0x3ad77bb4, 0x0d7a3660, 0xa89ecaf3, 0x2466ef97
    };
    
    uint8_t expected[4][4];
    for (int i = 0; i < AES_STATE_MATRIX_SPAN; i++) {
        expected[0][i] = (result[i] >> 24) & 0xFF;
        expected[1][i] = (result[i] >> 16) & 0xFF;
        expected[2][i] = (result[i] >>  8) & 0xFF;
        expected[3][i] =  result[i]        & 0xFF;
    }
    
    print_state(state);
    
    for (int i = 0; i < AES_STATE_MATRIX_SPAN; i++) {
        for (int j = 0; j < AES_STATE_MATRIX_SPAN; j++) {
            assert(state[i][j] == expected[i][j]);
        }
    }
    
    printf("\n\n");
    printf("✅ Test succeeded!\n");
    printf("\n\n");
    
    return 0;
}
