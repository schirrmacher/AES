
#ifndef aes_h
#define aes_h

#include <stdio.h>
#include "aes-constants.h"

void aes_256_encrypt_block(key input_key, block plaintext, block result_block_ref);

void aes_256_decrypt_block(key input_key, block ciphertext, block result_block_ref);

#endif /* aes_h */
