
#ifndef aes_h
#define aes_h

#include <stdio.h>
#include "aes-constants.h"

void aes_256_encrypt(const key input_key, block *plaintext, size_t size);

void aes_256_decrypt(const key input_key, block *ciphertext, size_t size);

#endif /* aes_h */
