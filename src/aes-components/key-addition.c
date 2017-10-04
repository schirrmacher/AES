
#include "key-addition.h"
#include "./key-schedule/key-schedule.h"


void add_round_key(const key input_key, state state_ref) {
    
    round_key round_key;
    get_round_key(input_key, round_key);
    
    for (int i = 0; i < AES_STATE_SPAN; i++) {
        for (int j = 0; j < AES_STATE_SPAN; j++) {
            state_ref[i][j] = round_key[i][j] ^ state_ref[i][j];
        }
    }
}

void inv_add_round_key(const key input_key, state state_ref) {
    
    round_key round_key;
    inv_get_round_key(input_key, round_key);
    
    for (int i = 0; i < AES_STATE_SPAN; i++) {
        for (int j = 0; j < AES_STATE_SPAN; j++) {
            state_ref[i][j] = round_key[i][j] ^ state_ref[i][j];
        }
    }
}
