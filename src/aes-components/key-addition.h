
#ifndef key_addition_h
#define key_addition_h

#include <stdio.h>
#include "aes-constants.h"

void add_round_key(key input_key, state state_ref);

void d_add_round_key(key input_key, state state_ref);

#endif /* key_addition_h */
