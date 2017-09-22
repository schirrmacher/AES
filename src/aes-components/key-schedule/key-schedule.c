
#include "key-schedule.h"
#include "g-function.h"
#include "h-function.h"


void get_round_key(word input_key[AES_256_KEY_WORDS], byte round_key[AES_STATE_SPAN][AES_STATE_SPAN]) {
    
    static int round = 0;
    static byte prev_key_state[AES_WORD_BYTES][AES_256_KEY_WORDS];
    
    if (round == 0) {
        
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                prev_key_state[i][j] = (input_key[j] >> (3 - i) * 8) & 0xFF;
                round_key[i][j] = prev_key_state[i][j];
            }
        }
        
    } else if (round == 1) {
        
        for (int i = 0; i < 4; i++) {
            for (int j = 4; j < 8; j++) {
                prev_key_state[i][j] = (input_key[j] >> (3 - i) * 8) & 0xFF;
                round_key[i][j - 4] = prev_key_state[i][j];
            }
        }
        
    } else if (round % 2 == 0) {
        
        byte g_word[AES_WORD_BYTES];
        for (int i = 0; i < AES_WORD_BYTES; i++) {
            g_word[i] = prev_key_state[i][7];
        }
        g(g_word);
        
        for (int i = 0; i < 4; i++) {
            round_key[i][0] = prev_key_state[i][0] ^ g_word[i];
            round_key[i][1] = round_key[i][0] ^ prev_key_state[i][1];
            round_key[i][2] = round_key[i][1] ^ prev_key_state[i][2];
            round_key[i][3] = round_key[i][2] ^ prev_key_state[i][3];
            
            for (int j = 0; j < 4; j++) {
                prev_key_state[i][j] = round_key[i][j];
            }
        }
        
    } else {
        
        byte h_word[AES_WORD_BYTES];
        for (int i = 0; i < AES_WORD_BYTES; i++) {
            h_word[i] = prev_key_state[i][3];
        }
        h(h_word);
        
        for (int i = 0; i < 4; i++) {
            round_key[i][0] = prev_key_state[i][4] ^ h_word[i];
            round_key[i][1] = round_key[i][0] ^ prev_key_state[i][5];
            round_key[i][2] = round_key[i][1] ^ prev_key_state[i][6];
            round_key[i][3] = round_key[i][2] ^ prev_key_state[i][7];
            
            for (int j = 4; j < 8; j++) {
                prev_key_state[i][j] = round_key[i][j - 4];
            }
        }
        
    }
    
    round++;
}
