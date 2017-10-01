
#include <stdio.h>
#include <string.h>
#include "./aes-constants.h"
#include "./substitute.h"
#include "./shift-rows.h"
#include "./mix-columns.h"
#include "./key-addition.h"


static void create_state_matrix(block plaintext, byte state[AES_STATE_SPAN][AES_STATE_SPAN]);
static void create_result_from_state(block result_block_ref, byte state[AES_STATE_SPAN][AES_STATE_SPAN]);

void aes_256_encrypt_block(block plaintext, key input_key, block result_block_ref) {
    
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
    
    create_result_from_state(result_block_ref, state);
    
}

static void create_state_matrix(block plaintext, byte state[AES_STATE_SPAN][AES_STATE_SPAN]) {
    for (int i = 0; i < AES_STATE_SPAN; i++) {
        state[0][i] = (plaintext[i] >> 24) & 0xFF;
        state[1][i] = (plaintext[i] >> 16) & 0xFF;
        state[2][i] = (plaintext[i] >>  8) & 0xFF;
        state[3][i] =  plaintext[i]        & 0xFF;
    }
}

static void create_result_from_state(block result_block_ref, byte state[AES_STATE_SPAN][AES_STATE_SPAN]) {
    for (int i = 0; i < AES_STATE_SPAN; i++) {
        result_block_ref[i] = state[0][i] << 24 | state[1][i] << 16 | state[2][i] << 8 | state[3][i];
    }
}
