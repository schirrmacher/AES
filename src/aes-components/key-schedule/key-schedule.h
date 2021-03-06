
#ifndef key_schedule_h
#define key_schedule_h

#include <stdio.h>
#include "../aes-constants.h"

void get_round_key(const key input_key, const int round, round_key round_key_ref);

void inv_get_round_key(const key input_key, const int round, round_key round_key_ref);

#endif /* key_schedule_h */
