
#include <stdio.h>
#include <string.h>
#include "./aes-constants.h"
#include "./substitute.h"
#include "./shift-rows.h"
#include "./mix-columns.h"
#include "./key-addition.h"


static void create_state_matrix(uint32_t plaintext[AES_PLAINTEXT_WORDS], byte state[AES_STATE_SPAN][AES_STATE_SPAN]);

void aes_256_encrypt_block(uint32_t plaintext[AES_PLAINTEXT_WORDS], key input_key, byte result[AES_STATE_SPAN][AES_STATE_SPAN]) {
    
    byte state[AES_STATE_SPAN][AES_STATE_SPAN];
    create_state_matrix(plaintext, state);
    
    add_round_key(input_key, state);
    
    for (int i = 1; i < AES_256_ROUNDS; i++) {
        substitute(state);
        shift_rows(state);
        mix_columns(state);
        add_round_key(input_key, state);
    }
    
    substitute(state);
    shift_rows(state);
    add_round_key(input_key, state);
    
    memcpy(result, state, sizeof(byte) * AES_STATE_SPAN * AES_STATE_SPAN);
    
}

static void create_state_matrix(uint32_t plaintext[AES_PLAINTEXT_WORDS], byte state[AES_STATE_SPAN][AES_STATE_SPAN]) {
    for (int i = 0; i < AES_STATE_SPAN; i++) {
        state[0][i] = (plaintext[i] >> 24) & 0xFF;
        state[1][i] = (plaintext[i] >> 16) & 0xFF;
        state[2][i] = (plaintext[i] >>  8) & 0xFF;
        state[3][i] =  plaintext[i]        & 0xFF;
    }
}
