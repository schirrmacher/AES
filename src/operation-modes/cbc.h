
#ifndef cbc_h
#define cbc_h

#include <stdio.h>


void cbc_encrypt(uint8_t *plaintext,
                 const size_t plaintext_bytes,
                 const size_t block_bytes,
                 const uint8_t *iv,
                 void (^encrypt)(uint8_t *block));

void cbc_decrypt(uint8_t *ciphertext,
                 const size_t ciphertext_bytes,
                 const size_t block_bytes,
                 const uint8_t *iv,
                 void (^decrypt)(uint8_t *block));

#endif /* cbc_h */
