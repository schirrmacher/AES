
#ifndef key_addition_h
#define key_addition_h

#include <stdio.h>
#include "aes-constants.h"

void add_round_key(uint32_t block[AES_STATE_MATRIX_SPAN], uint32_t key[AES_STATE_MATRIX_SPAN]);

#endif /* key_addition_h */
