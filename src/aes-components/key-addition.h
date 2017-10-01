
#ifndef key_addition_h
#define key_addition_h

#include <stdio.h>
#include "aes-constants.h"

void add_round_key(key input_key, byte state[AES_STATE_SPAN][AES_STATE_SPAN]);

#endif /* key_addition_h */
