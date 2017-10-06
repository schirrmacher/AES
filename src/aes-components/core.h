
#ifndef core_h
#define core_h

#include <stdio.h>
#include "aes-constants.h"

void aes_256_encrypt_block(const key input_key, const block plaintext, block result_block_ref);

void aes_256_decrypt_block(const key input_key, const block ciphertext, block result_block_ref);

#endif /* core_h */
