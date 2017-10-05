
#ifndef aes_h
#define aes_h

#include <stdio.h>
#include "aes-constants.h"

enum operation_mode {
    ECB,
    CBC
};

void aes_256_encrypt(const key input_key, block *plaintext, size_t size, enum operation_mode mode);

void aes_256_decrypt(const key input_key, block *ciphertext, size_t size, enum operation_mode mode);

#endif /* aes_h */
