
#include <stdio.h>
#include <string.h>
#include "./aes-constants.h"
#include "./substitute.h"
#include "./shift-rows.h"
#include "./mix-columns.h"
#include "./key-addition.h"


static void create_state_matrix(block plaintext, state state);
static void create_result_from_state(state state, block result_block_ref);

void aes_256_encrypt_block(key input_key, block plaintext, block result_block_ref) {
    
    state state_ref;
    create_state_matrix(plaintext, state_ref);
    
    add_round_key(input_key, state_ref);
    
    for (int i = 1; i < AES_256_ROUNDS; i++) {
        substitute(state_ref);
        shift_rows(state_ref);
        mix_columns(state_ref);
        add_round_key(input_key, state_ref);
    }
    
    substitute(state_ref);
    shift_rows(state_ref);
    add_round_key(input_key, state_ref);
    
    create_result_from_state(state_ref, result_block_ref);
    
}

static void create_state_matrix(block plaintext, state state) {
    for (int i = 0; i < AES_STATE_SPAN; i++) {
        state[0][i] = (plaintext[i] >> 24) & 0xFF;
        state[1][i] = (plaintext[i] >> 16) & 0xFF;
        state[2][i] = (plaintext[i] >>  8) & 0xFF;
        state[3][i] =  plaintext[i]        & 0xFF;
    }
}

static void create_result_from_state(state state, block result_block_ref) {
    for (int i = 0; i < AES_STATE_SPAN; i++) {
        result_block_ref[i] = state[0][i] << 24 | state[1][i] << 16 | state[2][i] << 8 | state[3][i];
    }
}
