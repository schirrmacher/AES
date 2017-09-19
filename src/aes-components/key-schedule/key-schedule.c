
#include "key-schedule.h"
#include "g-function.h"
#include <string.h>


void get_round_key(uint8_t key[AES_KEY_WORDS][AES_WORD_BYTES], uint8_t round_key[AES_KEY_WORDS][AES_WORD_BYTES]) {
    
    static int round = 0;
    static uint8_t prev_round_key[AES_KEY_WORDS][AES_WORD_BYTES];
    
    if (round == 0) {
        
        memcpy(round_key, key, sizeof(uint8_t) * AES_KEY_WORDS * AES_WORD_BYTES);
        
    } else {
        
        uint8_t g_word[AES_WORD_BYTES];
        for (int i = 0; i < AES_STATE_MATRIX_SPAN; i++) {
            g_word[i] = prev_round_key[i][3];
        }
        
        g(g_word);
        
        for (int i = 0; i < AES_STATE_MATRIX_SPAN; i++) {
            round_key[i][0] = prev_round_key[i][0] ^ g_word[i];
            round_key[i][1] = round_key[i][0] ^ prev_round_key[i][1];
            round_key[i][2] = round_key[i][1] ^ prev_round_key[i][2];
            round_key[i][3] = round_key[i][2] ^ prev_round_key[i][3];
        }
        
    }
    
    memcpy(prev_round_key, round_key, sizeof(uint8_t) * AES_KEY_WORDS * AES_WORD_BYTES);
    
    round++;
}
