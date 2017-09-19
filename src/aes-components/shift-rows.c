
#include "./shift-rows.h"
#include <string.h>
#include <limits.h>


void shift_rows(uint8_t state[AES_KEY_WORDS][AES_WORD_BYTES]) {
    
    uint8_t result[AES_KEY_WORDS][AES_WORD_BYTES];
    
    for (int i = 0; i < AES_STATE_MATRIX_SPAN; i++) {
        for (int j = 0; j < AES_STATE_MATRIX_SPAN; j++) {
            result[i][j] = state[i][(i + j) % AES_STATE_MATRIX_SPAN];
        }
    }
    
    memcpy(state, result, sizeof(uint8_t) * AES_STATE_MATRIX_SPAN * AES_WORD_BYTES);
}
