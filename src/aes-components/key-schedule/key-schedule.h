
#ifndef key_schedule_h
#define key_schedule_h

#include <stdio.h>
#include "../aes-constants.h"

void get_round_key(key input_key, round_key round_key_ref);

#endif /* key_schedule_h */
