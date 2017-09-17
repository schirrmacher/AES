
#ifndef util_h
#define util_h

#include <stdio.h>
#include <stdint.h>
#include "../aes-constants.h"

void create_initial_state(uint32_t plaintext[AES_WORD_BYTES], uint32_t state[AES_WORD_BYTES]);

void create_state_matrix(uint32_t state[AES_WORD_BYTES], uint8_t state_matrix[AES_STATE_MATRIX_SPAN][AES_STATE_MATRIX_SPAN]);

#endif /* util_h */
