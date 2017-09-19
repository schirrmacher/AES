
#include <stdio.h>
#include <string.h>
#include "./aes-constants.h"
#include "./substitute.h"
#include "./shift-rows.h"
#include "./mix-columns.h"
#include "./key-addition.h"


void aes_encrypt(uint32_t plaintext[AES_KEY_WORDS], uint32_t input_key[AES_KEY_WORDS], uint8_t result[AES_KEY_WORDS][AES_WORD_BYTES]) {
    
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
    
    memcpy(result, state, sizeof(uint8_t) * AES_KEY_WORDS * AES_WORD_BYTES);
    
}

