
#ifndef mix_columns_h
#define mix_columns_h

#include <stdio.h>
#include <stdint.h>
#include "aes-constants.h"

void mix_columns(uint8_t state[AES_KEY_WORDS][AES_WORD_BYTES]);

#endif /* mix_columns_h */
