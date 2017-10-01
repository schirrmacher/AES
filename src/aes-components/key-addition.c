
#include "key-addition.h"
#include "./key-schedule/key-schedule.h"
#include <string.h>


void add_round_key(key input_key, state state_ref) {
    
    round_key round_key_ref;
    get_round_key(input_key, round_key_ref);
    
    for (int i = 0; i < AES_STATE_SPAN; i++) {
        for (int j = 0; j < AES_STATE_SPAN; j++) {
            round_key_ref[i][j] ^= state_ref[i][j];
        }
    }
    
    memcpy(state_ref, round_key_ref, sizeof(byte) * AES_STATE_SPAN * AES_STATE_SPAN);
}
