
#include <string.h>
#include "util.h"


void create_initial_state(uint32_t plaintext[AES_WORD_BYTES], uint32_t state[AES_WORD_BYTES]) {
    uint8_t state_bytes[AES_STATE_MATRIX_SPAN][AES_STATE_MATRIX_SPAN];
    for (int i = 0; i < AES_STATE_MATRIX_SPAN; i++) {
        for (int j = 0; j < AES_STATE_MATRIX_SPAN; j++) {
            state_bytes[i][j] = (plaintext[3 - j] >> ((3 - i) * 8)) & 0xFF;
        }
    }
    memcpy(state, state_bytes, sizeof(uint32_t) * AES_KEY_WORDS);
}

void create_state_matrix(uint32_t state[AES_WORD_BYTES], uint8_t state_matrix[AES_STATE_MATRIX_SPAN][AES_STATE_MATRIX_SPAN]) {
    for (int i = 0; i < AES_STATE_MATRIX_SPAN; i++) {
        for (int j = 0; j < AES_STATE_MATRIX_SPAN; j++) {
            state_matrix[i][j] = (state[j] >> ((3 - i) * 8)) & 0xFF;
        }
    }
}
