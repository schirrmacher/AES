
#include <stdio.h>
#include <string.h>
#include "aes.h"
#include "core.h"


static void xor_blocks(const block first_block, const block second_block, block xored_block_ref);

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
