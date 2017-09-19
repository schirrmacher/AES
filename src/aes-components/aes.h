
#ifndef aes_h
#define aes_h

#include <stdio.h>
#include <stdint.h>
#include "aes-constants.h"

void aes_encrypt(uint32_t plaintext[AES_KEY_WORDS], uint32_t input_key[AES_KEY_WORDS], uint8_t result[AES_KEY_WORDS][AES_WORD_BYTES]);

#endif /* aes_h */
