
#ifndef aes_h
#define aes_h

#include <stdio.h>
#include "aes-constants.h"

enum operation_mode {
    ECB,
    CBC
};

struct aes_configuration {
    const key *key;
    const enum operation_mode mode;
    const block *iv;
};

void aes_256_encrypt(byte *plaintext, size_t plaintext_size, const struct aes_configuration config);

void aes_256_decrypt(byte *ciphertext, size_t ciphertext_size, const struct aes_configuration config);

#endif /* aes_h */
