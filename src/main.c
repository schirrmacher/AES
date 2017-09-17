
#include <stdio.h>
#include "./developer-utils/printing.h"
#include "./aes-components/aes-constants.h"
#include "./aes-components/substitute.h"
#include "./aes-components/shift-rows.h"
#include "./aes-components/mix-columns.h"
#include "./aes-components/key-addition.h"
#include <string.h>
#include <assert.h>

int main(int argc, const char * argv[]) {
    
    uint32_t key[4] = {
        0x2b7e1516, 0x28aed2a6, 0xabf71588, 0x09cf4f3c
    };
    
    uint32_t state[4] = {
        0x6bc1bee2, 0x2e409f96, 0xe93d7e11, 0x7393172a
    };
    
    printf("Key:\n");
    print_state(key, HEX);
    printf("\n");
    printf("Plaintext:\n");
    print_state(state, HEX);
    printf("\n");
    
    uint8_t state_bytes[AES_STATE_MATRIX_SPAN][AES_STATE_MATRIX_SPAN];
    for (int i = 0; i < AES_STATE_MATRIX_SPAN; i++) {
        state_bytes[0][3 - i] = (state[i] >> 24) & 0xFF;
        state_bytes[1][3 - i] = (state[i] >> 16) & 0xFF;
        state_bytes[2][3 - i] = (state[i] >>  8) & 0xFF;
        state_bytes[3][3 - i] =  state[i]        & 0xFF;
    }
    
    memcpy(state, state_bytes, sizeof(uint32_t) * AES_KEY_WORDS);
    
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
    
    for (int i = 0; i < AES_STATE_MATRIX_SPAN; i++) {
        state_bytes[0][i] = (state[i] >> 24) & 0xFF;
        state_bytes[1][i] = (state[i] >> 16) & 0xFF;
        state_bytes[2][i] = (state[i] >>  8) & 0xFF;
        state_bytes[3][i] =  state[i]        & 0xFF;
    }
    
    uint8_t expected[AES_STATE_MATRIX_SPAN][AES_STATE_MATRIX_SPAN] = {
        0x3a, 0xd7, 0x7b, 0xb4,
        0x0d, 0x7a, 0x36, 0x60,
        0xa8, 0x9e, 0xca, 0xf3,
        0x24, 0x66, 0xef, 0x97
    };
    
    for (int i = 0; i < AES_STATE_MATRIX_SPAN; i++) {
        for (int j = 0; j < AES_STATE_MATRIX_SPAN; j++) {
            print_hex_uint8(state_bytes[i][j]);
            assert(state_bytes[i][j] == expected[i][j]);
        }
    }
    
    printf("\n\n");
    printf("✅ Test succeeded!\n");
    printf("\n\n");
    
    return 0;
}
