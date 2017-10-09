
#include "core.h"
#include "./aes-constants.h"
#include "./substitute.h"
#include "./shift-rows.h"
#include "./mix-columns.h"
#include "./key-addition.h"


static void create_state_from_block(const block plaintext, state state_ref);
static void create_block_from_state(const state state, block result_block_ref);

void aes_256_encrypt_block(const key input_key, const block plaintext, block result_block_ref) {
    
    int round = 0;
    state state;
    create_state_from_block(plaintext, state);
    
    add_round_key(input_key, round++, state);
    
    for (; round < AES_256_ROUNDS; round++) {
        substitute(state);
        shift_rows(state);
        mix_columns(state);
        add_round_key(input_key, round, state);
    }
    
    substitute(state);
    shift_rows(state);
    add_round_key(input_key, round, state);
    
    create_block_from_state(state, result_block_ref);
    
}

void aes_256_decrypt_block(const key input_key, const block ciphertext, block result_block_ref) {
    
    int round = AES_256_ROUNDS;
    state state;
    create_state_from_block(ciphertext, state);
    
    inv_add_round_key(input_key, round--, state);
    inv_shift_rows(state);
    inv_substitute(state);
    
    for (; 0 < round; round--) {
        inv_add_round_key(input_key, round, state);
        inv_mix_columns(state);
        inv_shift_rows(state);
        inv_substitute(state);
    }
    
    inv_add_round_key(input_key, round, state);
    
    create_block_from_state(state, result_block_ref);
    
}

static void create_state_from_block(const block block, state state_ref) {
    for (int i = 0; i < AES_STATE_SPAN; i++) {
        for (int j = 0; j < AES_STATE_SPAN; j++) {
            state_ref[i][j] = block[i + (j * AES_STATE_SPAN)];
        }
    }
}

static void create_block_from_state(const state state, block block_ref) {
    for (int i = 0; i < AES_STATE_SPAN; i++) {
        for (int j = 0; j < AES_STATE_SPAN; j++) {
            block_ref[i + (j * AES_STATE_SPAN)] = state[i][j];
        }
    }
}
