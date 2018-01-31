
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "aes.h"
#include "core.h"
#include "../operation-modes/cbc.h"
#include "../operation-modes/ecb.h"


void aes_256_encrypt(byte *plaintext, size_t plaintext_size, const struct aes_configuration config) {

    switch (config.mode) {

        case ECB:

            ecb_encrypt(plaintext, plaintext_size, AES_BLOCK_BYTES, ^(uint8_t *block) {
                aes_256_encrypt_block(*config.key, block, block);
            });

            break;

        case CBC:

            cbc_encrypt(plaintext, plaintext_size, AES_BLOCK_BYTES, *config.iv, ^(uint8_t *block) {
                aes_256_encrypt_block(*config.key, block, block);
            });

            break;

    }

}

void aes_256_decrypt(byte *ciphertext, size_t ciphertext_size, const struct aes_configuration config) {

    switch (config.mode) {

        case ECB:

            ecb_decrypt(ciphertext, ciphertext_size, AES_BLOCK_BYTES, ^(uint8_t *block) {
                aes_256_decrypt_block(*config.key, block, block);
            });

            break;

        case CBC:

            cbc_decrypt(ciphertext, ciphertext_size, AES_BLOCK_BYTES, *config.iv, ^(uint8_t *block) {
                aes_256_decrypt_block(*config.key, block, block);
            });

            break;

    }

}
