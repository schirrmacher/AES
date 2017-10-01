
#ifndef aes_h
#define aes_h

#include <stdio.h>
#include "aes-constants.h"

void aes_256_encrypt_block(uint32_t plaintext[AES_PLAINTEXT_WORDS], key input_key, byte result[AES_STATE_SPAN][AES_STATE_SPAN]);

#endif /* aes_h */
