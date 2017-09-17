
#include <stdio.h>
#include "./developer-utils/printing.h"
#include "./aes-components/aes-constants.h"
#include "./aes-components/substitute.h"
#include "./aes-components/shift-rows.h"
#include "./aes-components/mix-columns.h"
#include "./aes-components/key-addition.h"
#include <string.h>

int main(int argc, const char * argv[]) {
    
    uint32_t key[4] = {
        0x2b7e1516, 0x28aed2a6, 0xabf71588, 0x09cf4f3c
    };
    
    uint32_t state[4] = {
        0x6bc1bee2, 0x2e409f96, 0xe93d7e11, 0x7393172a
    };
    
    uint8_t state_bytes[AES_STATE_MATRIX_SPAN][AES_STATE_MATRIX_SPAN];
    for (int i = 0; i < AES_STATE_MATRIX_SPAN; i++) {
        state_bytes[0][3 - i] = (state[i] >> 24) & 0xFF;
        state_bytes[1][3 - i] = (state[i] >> 16) & 0xFF;
        state_bytes[2][3 - i] = (state[i] >>  8) & 0xFF;
        state_bytes[3][3 - i] =  state[i]        & 0xFF;
    }
    
    memcpy(state, state_bytes, sizeof(uint32_t) * AES_KEY_WORDS);
    
    add_round_key(state, key);
    printf("Add initial round-key:\n");
    print_state(state, HEX);
    
    for (int i = 1; i <= 9; i++) {
        substitute(state);
        printf("Substitute:\n");
        print_state(state, HEX);
        
        shift_rows(state);
        printf("Shift rows:\n");
        print_state(state, HEX);
        
        mix_columns(state);
        printf("Mix columns:\n");
        print_state(state, HEX);
        
        printf("Add round-key:\n");
        add_round_key(state, key);
        print_state(state, HEX);
    }
    
    substitute(state);
    print_state(state, HEX);
    
    shift_rows(state);
    print_state(state, HEX);
    
    add_round_key(state, key);
    print_state(state, HEX);
    
    return 0;
}
