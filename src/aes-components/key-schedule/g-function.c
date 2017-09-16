
#include <string.h>
#include <limits.h>

#include "g-function.h"
#include "../aes-constants.h"
#include "substitute.h"


static void rotate_bytes_left_by_one(uint8_t* word);
static uint round_constant(void);

uint32_t g(uint32_t word) {
    
    uint8_t word_bytes[4];
    word_bytes[0] = (word >> 24) & 0xFF;
    word_bytes[1] = (word >> 16) & 0xFF;
    word_bytes[2] = (word >> 8) & 0xFF;
    word_bytes[3] = word & 0xFF;
    
    rotate_bytes_left_by_one(word_bytes);
    
    for(int i = 0; i < 4; i++) {
        word_bytes[i] = substitutes[word_bytes[i]];
    }
    
    word_bytes[0] ^= round_constant();
    
    return word_bytes[0] << 24 | word_bytes[1] << 16 | word_bytes[2] << 8 | word_bytes[3];
}

static void rotate_bytes_left_by_one(uint8_t* word) {
    uint8_t result[AES_STATE_MATRIX_SPAN];
    for (int i = 0; i < AES_STATE_MATRIX_SPAN; i++) {
        int targetIndex = (i + 3) % AES_STATE_MATRIX_SPAN;
        result[targetIndex] = word[i];
    }
    memcpy(word, result, sizeof(uint8_t) * AES_STATE_MATRIX_SPAN);
}

static uint round_constant() {
    static int round = 0;
    uint result = 1;
    for (int i = 0; i < round; i++) {
        result <<= 1;
        if (0xFF < result) {
            result ^= AES_IRREDUCIBLE_POLYNOMIAL;
        }
    }
    round++;
    return result;
}
