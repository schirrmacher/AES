
#include "key-addition.h"
#include "./key-schedule/key-schedule.h"
#include <string.h>


void add_round_key(uint32_t state[AES_STATE_MATRIX_SPAN], uint32_t key[AES_STATE_MATRIX_SPAN]) {
    
    uint32_t round_key[AES_STATE_MATRIX_SPAN];
    get_round_key(key, round_key);
    
    uint8_t state_bytes[AES_STATE_MATRIX_SPAN][AES_STATE_MATRIX_SPAN];
    for (int i = 0; i < AES_STATE_MATRIX_SPAN; i++) {
        state_bytes[i][3] = (state[i] >> 24) & 0xFF;
        state_bytes[i][2] = (state[i] >> 16) & 0xFF;
        state_bytes[i][1] = (state[i] >>  8) & 0xFF;
        state_bytes[i][0] =  state[i]        & 0xFF;
    }
    
    uint8_t round_key_bytes[AES_STATE_MATRIX_SPAN][AES_STATE_MATRIX_SPAN];
    for (int i = 0; i < AES_STATE_MATRIX_SPAN; i++) {
        round_key_bytes[0][3 - i] = (round_key[i] >> 24) & 0xFF;
        round_key_bytes[1][3 - i] = (round_key[i] >> 16) & 0xFF;
        round_key_bytes[2][3 - i] = (round_key[i] >>  8) & 0xFF;
        round_key_bytes[3][3 - i] =  round_key[i]        & 0xFF;
    }
    
    for (int i = 0; i < AES_STATE_MATRIX_SPAN; i++) {
        for (int j = 0; j < AES_STATE_MATRIX_SPAN; j++) {
            round_key_bytes[i][j] ^= state_bytes[i][j];
        }
    }
    
    memcpy(state, round_key_bytes, sizeof(uint32_t) * AES_KEY_WORDS);
}
