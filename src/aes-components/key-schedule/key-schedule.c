
#include "key-schedule.h"
#include "g-function.h"
#include "h-function.h"


static void compute_round_keys(key input_key, round_key round_keys[AES_256_ROUNDS + 1]);

void get_round_key(key input_key, round_key round_key_ref) {
    
    static int round = 0;
    
    static round_key round_keys[AES_256_ROUNDS + 1];
    
    if (round == 0) {
        compute_round_keys(input_key, round_keys);
    }
    
    for (int i = 0; i < AES_STATE_SPAN; i++) {
        for (int j = 0; j < AES_STATE_SPAN; j++) {
            round_key_ref[i][j] = round_keys[round][i][j];
        }
    }
    
    round++;
}

static void compute_round_keys(key input_key, round_key round_keys_ref[AES_256_ROUNDS + 1]) {
    
    for (int round = 0; round < AES_256_ROUNDS + 1; round++) {
        
        if (round == 0) {
            
            for (int i = 0; i < AES_STATE_SPAN; i++) {
                for (int j = 0; j < AES_STATE_SPAN; j++) {
                    round_keys_ref[round][i][j] = (input_key[j] >> (3 - i) * 8) & 0xFF;
                }
            }
            
        } else if (round == 1) {
            
            for (int i = 0; i < AES_STATE_SPAN; i++) {
                for (int j = 0; j < AES_STATE_SPAN; j++) {
                    round_keys_ref[round][i][j] = (input_key[j + 4] >> (3 - i) * 8) & 0xFF;
                }
            }
            
        } else {
            
            word prev_last_word;
            for (int i = 0; i < AES_WORD_BYTES; i++) {
                prev_last_word[i] = round_keys_ref[round - 1][i][3];
            }
            
            if (round % 2 == 0)
                g(prev_last_word);
            else
                h(prev_last_word);
            
            for (int i = 0; i < AES_STATE_SPAN; i++) {
                round_keys_ref[round][i][0] = round_keys_ref[round - 2][i][0] ^ prev_last_word[i];
                
                for (int j = 1; j < AES_STATE_SPAN; j++) {
                    round_keys_ref[round][i][j] = round_keys_ref[round][i][j - 1] ^ round_keys_ref[round - 2][i][j];
                }
            }
            
        }
    }
    
}
