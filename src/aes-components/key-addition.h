
#ifndef key_addition_h
#define key_addition_h

#include <stdio.h>
#include "aes-constants.h"

void add_round_key(const key input_key, const int round, state state_ref);

void inv_add_round_key(const key input_key, const int round, state state_ref);

#endif /* key_addition_h */
