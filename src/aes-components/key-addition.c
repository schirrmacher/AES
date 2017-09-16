
#include "key-addition.h"
#include "key-schedule.h"


void add_round_key(uint32_t block[AES_STATE_MATRIX_SPAN], uint32_t key[AES_STATE_MATRIX_SPAN]) {
    
    uint32_t round_key[AES_STATE_MATRIX_SPAN];
    get_round_key(key, round_key);
    
    for (int i = 0; i < AES_STATE_MATRIX_SPAN; i++) {
        block[i] ^= round_key[i];
    }
}
