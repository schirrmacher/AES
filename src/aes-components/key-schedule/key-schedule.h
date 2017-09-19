
#ifndef key_schedule_h
#define key_schedule_h

#include <stdio.h>
#include <stdint.h>
#include "../aes-constants.h"

void get_round_key(uint8_t key[AES_KEY_WORDS][AES_WORD_BYTES], uint8_t round_key[AES_KEY_WORDS][AES_WORD_BYTES]);

#endif /* key_schedule_h */
