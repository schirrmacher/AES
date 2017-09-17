
#ifndef key_schedule_h
#define key_schedule_h

#include <stdio.h>
#include "aes-constants.h"

void get_round_key(uint32_t key[AES_KEY_WORDS], uint32_t round_key[AES_KEY_WORDS]);

#endif /* key_schedule_h */
