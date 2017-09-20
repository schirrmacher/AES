
#include "key-schedule.h"
#include "g-function.h"
#include <string.h>


static void create_key_matrix(word key[AES_128_KEY_WORDS], byte state[AES_STATE_SPAN][AES_STATE_SPAN]);

void get_round_key(word input_key[AES_128_KEY_WORDS], byte round_key[AES_STATE_SPAN][AES_STATE_SPAN]) {
    
    static int round = 0;
    static byte prev_round_key[AES_128_KEY_WORDS][AES_WORD_BYTES];
    
    if (round == 0) {
        
        byte key_matrix[AES_128_KEY_WORDS][AES_WORD_BYTES];
        create_key_matrix(input_key, key_matrix);
        
        memcpy(round_key, key_matrix, sizeof(byte) * AES_128_KEY_WORDS * AES_WORD_BYTES);
        
    } else {
        
        byte g_word[AES_WORD_BYTES];
        for (int i = 0; i < AES_WORD_BYTES; i++) {
            g_word[i] = prev_round_key[i][3];
        }
        
        g(g_word);
        
        for (int i = 0; i < AES_STATE_SPAN; i++) {
            round_key[i][0] = prev_round_key[i][0] ^ g_word[i];
            round_key[i][1] = round_key[i][0] ^ prev_round_key[i][1];
            round_key[i][2] = round_key[i][1] ^ prev_round_key[i][2];
            round_key[i][3] = round_key[i][2] ^ prev_round_key[i][3];
        }
        
    }
    
    memcpy(prev_round_key, round_key, sizeof(byte) * AES_128_KEY_WORDS * AES_WORD_BYTES);
    
    round++;
}

static void create_key_matrix(word key[AES_128_KEY_WORDS], byte key_matrix[AES_STATE_SPAN][AES_STATE_SPAN]) {
    for (int i = 0; i < AES_STATE_SPAN; i++) {
        key_matrix[0][i] = (key[i] >> 24) & 0xFF;
        key_matrix[1][i] = (key[i] >> 16) & 0xFF;
        key_matrix[2][i] = (key[i] >>  8) & 0xFF;
        key_matrix[3][i] =  key[i]        & 0xFF;
    }
}
