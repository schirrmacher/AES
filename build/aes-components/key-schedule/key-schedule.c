
#include "key-schedule.h"
#include "g-function.h"
#include <string.h>

void get_round_key(uint32_t key[AES_KEY_WORDS], uint32_t round_key[AES_KEY_WORDS]) {
    
    static int round = 0;
    static uint32_t prev_round_key[AES_KEY_WORDS];
    
    if (round == 0) {
        memcpy(prev_round_key, key, sizeof(uint32_t) * AES_KEY_WORDS);
        memcpy(round_key, key, sizeof(uint32_t) * AES_KEY_WORDS);
    } else {
        round_key[0] = prev_round_key[0] ^ g(prev_round_key[3]);
        round_key[1] = round_key[0] ^ prev_round_key[1];
        round_key[2] = round_key[1] ^ prev_round_key[2];
        round_key[3] = round_key[2] ^ prev_round_key[3];
        memcpy(prev_round_key, round_key, sizeof(uint32_t) * AES_KEY_WORDS);
    }
    
    round++;
}
