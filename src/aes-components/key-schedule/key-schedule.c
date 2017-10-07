
#include "key-schedule.h"
#include "g-function.h"
#include "h-function.h"


static void compute_round_keys(const key input_key, round_key round_keys[AES_256_ROUNDS + 1]);

void get_round_key(const key input_key, const int round, round_key round_key_ref) {
    
    static round_key round_keys[AES_256_ROUNDS + 1];
    
    if (round == 0) {
        compute_round_keys(input_key, round_keys);
    }
    
    for (int i = 0; i < AES_STATE_SPAN; i++) {
        for (int j = 0; j < AES_STATE_SPAN; j++) {
            round_key_ref[i][j] = round_keys[round][i][j];
        }
    }
}

void inv_get_round_key(const key input_key, const int round, round_key round_key_ref) {
    
    static round_key round_keys[AES_256_ROUNDS + 1];
    
    if (round == AES_256_ROUNDS) {
        compute_round_keys(input_key, round_keys);
    }
    
    for (int i = 0; i < AES_STATE_SPAN; i++) {
        for (int j = 0; j < AES_STATE_SPAN; j++) {
            round_key_ref[i][j] = round_keys[round][i][j];
        }
    }
}

static void compute_round_keys(const key input_key, round_key round_keys_ref[AES_256_ROUNDS + 1]) {
    
    int g_round = 1;
    
    for (int round_key_count = 0; round_key_count < AES_256_ROUNDS + 1; round_key_count++) {
        
        if (round_key_count == 0 || round_key_count == 1) {
            
            int key_byte_offset = round_key_count * (AES_256_KEY_BYTES / 2);
            
            for (int i = 0; i < AES_STATE_SPAN; i++) {
                for (int j = 0; j < AES_STATE_SPAN; j++) {
                    int key_byte_index = i + (j * AES_STATE_SPAN) + key_byte_offset;
                    round_keys_ref[round_key_count][i][j] = input_key[key_byte_index];
                }
            }
            
        } else {
            
            word prev_last_word;
            for (int i = 0; i < AES_WORD_BYTES; i++) {
                prev_last_word[i] = round_keys_ref[round_key_count - 1][i][3];
            }
            
            if (round_key_count % 2 == 0)
                g(g_round++, prev_last_word);
            else
                h(prev_last_word);
            
            for (int i = 0; i < AES_STATE_SPAN; i++) {
                
                round_keys_ref[round_key_count][i][0] = round_keys_ref[round_key_count - 2][i][0] ^ prev_last_word[i];
                
                for (int j = 1; j < AES_STATE_SPAN; j++) {
                    round_keys_ref[round_key_count][i][j] = round_keys_ref[round_key_count][i][j - 1] ^ round_keys_ref[round_key_count - 2][i][j];
                }
            }
            
        }
        
    }
}
