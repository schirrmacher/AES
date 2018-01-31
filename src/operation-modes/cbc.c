
#include "cbc.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "block-processing.h"


static void xor_blocks(const uint8_t *first_block,
                       const uint8_t *second_block,
                       const size_t block_size,
                       uint8_t *xored_block_ref);

void cbc_encrypt(uint8_t *plaintext,
                 const size_t plaintext_bytes,
                 const size_t block_bytes,
                 const uint8_t *iv,
                 void (^encrypt)(uint8_t *block))
{

    process_blocks(plaintext, plaintext_bytes, block_bytes, ^(uint8_t *block, unsigned long index) {

        if (index == 0)
            xor_blocks(block, iv, block_bytes, block);
        else {
            uint8_t *prev = plaintext + (block_bytes * (index - 1));
            xor_blocks(block, prev, block_bytes, block);
        }

        encrypt(block);

    });
}

void cbc_decrypt(uint8_t *ciphertext,
                 const size_t ciphertext_bytes,
                 const size_t block_bytes,
                 const uint8_t *iv,
                 void (^decrypt)(uint8_t *block))
{

    uint8_t *prev_block = malloc(block_bytes * sizeof(uint8_t));
    uint8_t *temp = malloc(block_bytes * sizeof(uint8_t));

    process_blocks(ciphertext, ciphertext_bytes, block_bytes, ^(uint8_t *block, unsigned long index) {

        if (index == 0) {
            memcpy(prev_block, block, block_bytes * sizeof(uint8_t));
            decrypt(block);
            xor_blocks(block, iv, block_bytes, block);
        } else {
            memcpy(temp, block, block_bytes * sizeof(uint8_t));
            decrypt(block);
            xor_blocks(block, prev_block, block_bytes, block);
            memcpy(prev_block, temp, block_bytes * sizeof(uint8_t));
        }

    });

    free(prev_block);
    free(temp);
}

static void xor_blocks(const uint8_t *first_block,
                       const uint8_t *second_block,
                       const size_t block_size,
                       uint8_t *xored_block_ref)
{
    for (int i = 0; i < block_size; i++) {
        xored_block_ref[i] = first_block[i] ^ second_block[i];
    }
}
