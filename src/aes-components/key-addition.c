
#include "key-addition.h"
#include "./key-schedule/key-schedule.h"
#include <string.h>


void add_round_key(uint8_t state[AES_KEY_WORDS][AES_WORD_BYTES], uint8_t key[AES_KEY_WORDS][AES_WORD_BYTES]) {
    
    uint8_t round_key[AES_KEY_WORDS][AES_WORD_BYTES];
    get_round_key(key, round_key);
    
    for (int i = 0; i < AES_STATE_MATRIX_SPAN; i++) {
        for (int j = 0; j < AES_STATE_MATRIX_SPAN; j++) {
            round_key[i][j] ^= state[i][j];
        }
    }
    
    memcpy(state, round_key, sizeof(uint8_t) * AES_STATE_MATRIX_SPAN * AES_WORD_BYTES);
}
