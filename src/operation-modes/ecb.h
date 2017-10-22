
#ifndef ecb_h
#define ecb_h

#include <stdio.h>

void ecb_encrypt(uint8_t *plaintext,
                 const size_t plaintext_bytes,
                 const size_t block_bytes,
                 void (^encrypt)(uint8_t *block));

void ecb_decrypt(uint8_t *ciphertext,
                 const size_t ciphertext_bytes,
                 const size_t block_bytes,
                 void (^decrypt)(uint8_t *block));

#endif /* ecb_h */
