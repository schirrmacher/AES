
#ifndef aes_h
#define aes_h

#include <stdio.h>
#include "aes-constants.h"

void aes_encrypt(word plaintext[AES_PLAINTEXT_WORDS], word input_key[AES_128_KEY_WORDS], byte result[AES_STATE_SPAN][AES_STATE_SPAN]);

#endif /* aes_h */
