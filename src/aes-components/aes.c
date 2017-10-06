
#include <stdio.h>
#include <string.h>
#include "aes.h"
#include "./aes-constants.h"
#include "./substitute.h"
#include "./shift-rows.h"
#include "./mix-columns.h"
#include "./key-addition.h"


static void xor_blocks(const block first_block, const block second_block, block xored_block_ref);

static void aes_256_encrypt_block(const key input_key, const block plaintext, block result_block_ref);
static void aes_256_decrypt_block(const key input_key, const block ciphertext, block result_block_ref);

static void create_state_from_block(const block plaintext, state state_ref);
static void create_block_from_state(const state state, block result_block_ref);

void aes_256_encrypt(block *plaintext, size_t plaintext_size, const struct aes_configuration config) {
    
    if (config.mode == ECB) {
        for (int i = 0; i < plaintext_size; i++) {
            aes_256_encrypt_block(*config.key, plaintext[i], plaintext[i]);
        }
        return;
    }
    
    for (int i = 0; i < plaintext_size; i++) {
    
        block temp_result;
        if (i == 0)
            xor_blocks(plaintext[i], *config.iv, temp_result);
        else
            xor_blocks(plaintext[i], plaintext[i - 1], temp_result);
        
        aes_256_encrypt_block(*config.key, temp_result, plaintext[i]);
    }
}

void aes_256_decrypt(block *ciphertext, size_t ciphertext_size, const struct aes_configuration config) {
    
    if (config.mode == ECB) {
        for (int i = 0; i < ciphertext_size; i++) {
            aes_256_decrypt_block(*config.key, ciphertext[i], ciphertext[i]);
        }
        return;
    }
    
    block prev_ciphertext;
    for (int i = 0; i < ciphertext_size; i++) {
        
        block temp_result;
        aes_256_decrypt_block(*config.key, ciphertext[i], temp_result);
        
        if (i == 0) {
            memcpy(prev_ciphertext, ciphertext[0], sizeof(block));
            xor_blocks(temp_result, *config.iv, ciphertext[i]);
        } else {
            block temp_ciphertext;
            xor_blocks(temp_result, prev_ciphertext, temp_ciphertext);
            memcpy(prev_ciphertext, ciphertext[i], sizeof(block));
            memcpy(ciphertext[i], temp_ciphertext, sizeof(block));
        }
    }
}

static void xor_blocks(const block first_block, const block second_block, block xored_block_ref) {
    for (int i = 0; i < 4; i++) {
        xored_block_ref[i] = first_block[i] ^ second_block[i];
    }
}

static void aes_256_encrypt_block(const key input_key, const block plaintext, block result_block_ref) {
    
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

static void aes_256_decrypt_block(const key input_key, const block ciphertext, block result_block_ref) {
    
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
