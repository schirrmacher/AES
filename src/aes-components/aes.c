
#include <stdio.h>
#include <string.h>
#include "aes.h"
#include "core.h"


static void xor_blocks(const block first_block, const block second_block, block xored_block_ref);

void aes_256_encrypt(byte *plaintext, size_t plaintext_size, const struct aes_configuration config) {
    
    if (plaintext_size % AES_BLOCK_BYTES != 0) {
        // error
    }
    
    const unsigned long blocks = plaintext_size / AES_BLOCK_BYTES;
    
    block prev_result;
    for (int i = 0; i < blocks; i++) {
        
        block text_block;
        memcpy(text_block, plaintext + (i * AES_BLOCK_BYTES), sizeof(block));
        
        block temp_result;
        
        switch (config.mode) {
                
            case ECB:
                aes_256_encrypt_block(*config.key, text_block, text_block);
                break;
                
            case CBC:
                if (i == 0)
                    xor_blocks(text_block, *config.iv, temp_result);
                else
                    xor_blocks(text_block, prev_result, temp_result);
                
                aes_256_encrypt_block(*config.key, temp_result, text_block);
                break;
        }
        
        memcpy(prev_result, text_block, sizeof(block));
        memcpy(plaintext + (i * AES_BLOCK_BYTES), text_block, sizeof(block));
    }
    
}

void aes_256_decrypt(byte *ciphertext, size_t ciphertext_size, const struct aes_configuration config) {
    
    block prev_ciphertext;
    block prev_result;
    
    for (int i = 0; i < ciphertext_size / AES_BLOCK_BYTES; i++) {
        
        block text_block;
        block temp_result;
        
        memcpy(text_block, ciphertext + (i * AES_BLOCK_BYTES), sizeof(block));
        
        switch (config.mode) {
                
            case ECB:
                aes_256_decrypt_block(*config.key, text_block, text_block);
                break;
                
            case CBC:
                
                aes_256_decrypt_block(*config.key, text_block, temp_result);
                
                if (i == 0) {
                    memcpy(prev_ciphertext, text_block, sizeof(block));
                    xor_blocks(temp_result, *config.iv, text_block);
                } else {
                    block temp_ciphertext;
                    xor_blocks(temp_result, prev_ciphertext, temp_ciphertext);
                    memcpy(prev_ciphertext, text_block, sizeof(block));
                    memcpy(text_block, temp_ciphertext, sizeof(block));
                }
                break;
        }
        
        memcpy(prev_result, text_block, sizeof(block));
        memcpy(ciphertext + (i * AES_BLOCK_BYTES), text_block, sizeof(block));
    }
}

static void xor_blocks(const block first_block, const block second_block, block xored_block_ref) {
    for (int i = 0; i < AES_BLOCK_BYTES; i++) {
        xored_block_ref[i] = first_block[i] ^ second_block[i];
    }
}
