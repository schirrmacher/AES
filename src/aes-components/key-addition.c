
#include "key-addition.h"
#include "./key-schedule/key-schedule.h"
#include <string.h>


void add_round_key(key input_key, state state) {
    
    byte round_key[AES_STATE_SPAN][AES_STATE_SPAN];
    get_round_key(input_key, round_key);
    
    for (int i = 0; i < AES_STATE_SPAN; i++) {
        for (int j = 0; j < AES_STATE_SPAN; j++) {
            round_key[i][j] ^= state[i][j];
        }
    }
    
    memcpy(state, round_key, sizeof(byte) * AES_STATE_SPAN * AES_STATE_SPAN);
}
