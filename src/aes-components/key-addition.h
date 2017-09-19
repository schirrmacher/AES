
#ifndef key_addition_h
#define key_addition_h

#include <stdio.h>
#include <stdint.h>
#include "aes-constants.h"

void add_round_key(uint8_t state[AES_KEY_WORDS][AES_WORD_BYTES], uint8_t key[AES_KEY_WORDS][AES_WORD_BYTES]);

#endif /* key_addition_h */
