
#ifndef key_schedule_h
#define key_schedule_h

#include <stdio.h>
#include "../aes-constants.h"

void get_round_key(word input_key[AES_128_KEY_WORDS], byte round_key[AES_STATE_SPAN][AES_STATE_SPAN]);

#endif /* key_schedule_h */
