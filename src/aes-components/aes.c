
#include <stdio.h>
#include <string.h>
#include "./aes-constants.h"
#include "./substitute.h"
#include "./shift-rows.h"
#include "./mix-columns.h"
#include "./key-addition.h"


static void create_state_from_block(const block plaintext, state state_ref);
static void create_block_from_state(const state state, block result_block_ref);

void aes_256_encrypt_block(const key input_key, const block plaintext, block result_block_ref) {
    
    state state;
    create_state_from_block(plaintext, state);
    
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
    
    create_block_from_state(state, result_block_ref);
    
}

void aes_256_decrypt_block(const key input_key, const block ciphertext, block result_block_ref) {
    
    state state;
    create_state_from_block(ciphertext, state);
    
    inv_add_round_key(input_key, state);
    inv_shift_rows(state);
    inv_substitute(state);
    
    for (int i = 1; i < AES_256_ROUNDS; i++) {
        inv_add_round_key(input_key, state);
        inv_mix_columns(state);
        inv_shift_rows(state);
        inv_substitute(state);
    }
    
    inv_add_round_key(input_key, state);
    
    create_block_from_state(state, result_block_ref);
    
}

static void create_state_from_block(const block block, state state_ref) {
    for (int i = 0; i < AES_STATE_SPAN; i++) {
        state_ref[0][i] = (block[i] >> 24) & 0xFF;
        state_ref[1][i] = (block[i] >> 16) & 0xFF;
        state_ref[2][i] = (block[i] >>  8) & 0xFF;
        state_ref[3][i] =  block[i]        & 0xFF;
    }
}

static void create_block_from_state(const state state, block block_ref) {
    for (int i = 0; i < AES_STATE_SPAN; i++) {
        block_ref[i] = state[0][i] << 24 | state[1][i] << 16 | state[2][i] << 8 | state[3][i];
    }
}
