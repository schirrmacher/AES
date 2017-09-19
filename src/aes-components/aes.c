
#include <stdio.h>
#include <string.h>
#include "./aes-constants.h"
#include "./substitute.h"
#include "./shift-rows.h"
#include "./mix-columns.h"
#include "./key-addition.h"


static void transform_to_matrix(uint32_t plaintext[AES_KEY_WORDS], uint8_t state[AES_KEY_WORDS][AES_WORD_BYTES]);

void aes_encrypt(uint32_t plaintext[AES_KEY_WORDS], uint32_t input_key[AES_KEY_WORDS], uint8_t result[AES_KEY_WORDS][AES_WORD_BYTES]) {
    
    uint8_t key[4][4];
    transform_to_matrix(input_key, key);
    
    uint8_t state[4][4];
    transform_to_matrix(plaintext, state);
    
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

static void transform_to_matrix(uint32_t input[AES_KEY_WORDS], uint8_t state[AES_KEY_WORDS][AES_WORD_BYTES]) {
    for (int i = 0; i < AES_STATE_MATRIX_SPAN; i++) {
        state[0][i] = (input[i] >> 24) & 0xFF;
        state[1][i] = (input[i] >> 16) & 0xFF;
        state[2][i] = (input[i] >>  8) & 0xFF;
        state[3][i] =  input[i]        & 0xFF;
    }
}
