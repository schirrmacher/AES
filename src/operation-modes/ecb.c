
#include "ecb.h"
#include "block-processing.h"


void ecb_encrypt(uint8_t *plaintext,
                 const size_t plaintext_bytes,
                 const size_t block_bytes,
                 void (^encrypt)(uint8_t *block))
{
    process_blocks(plaintext, plaintext_bytes, block_bytes, ^(uint8_t *block, unsigned long index) {
        encrypt(block);
    });
}

void ecb_decrypt(uint8_t *ciphertext,
                 const size_t ciphertext_bytes,
                 const size_t block_bytes,
                 void (^decrypt)(uint8_t *block))
{
    process_blocks(ciphertext, ciphertext_bytes, block_bytes, ^(uint8_t *block, unsigned long index) {
        decrypt(block);
    });
}
