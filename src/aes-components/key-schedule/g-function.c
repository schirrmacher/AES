
#include <string.h>
#include <limits.h>
#include "g-function.h"
#include "../substitute.h"


static void rotate_bytes_left_by_one(word word);
static int round_constant(void);

void g(word word) {
    rotate_bytes_left_by_one(word);
    for(int i = 0; i < AES_WORD_BYTES; i++) {
        word[i] = substitutes[word[i]];
    }
    word[0] ^= round_constant();
}

static void rotate_bytes_left_by_one(word word) {
    byte result[AES_WORD_BYTES];
    for (int i = 0; i < AES_WORD_BYTES; i++) {
        int targetIndex = (i + 3) % AES_WORD_BYTES;
        result[targetIndex] = word[i];
    }
    memcpy(word, result, sizeof(byte) * AES_WORD_BYTES);
}

static int round_constant() {
    static int round = 0;
    int result = 1;
    for (int i = 0; i < round; i++) {
        result <<= 1;
        if (0xFF < result) {
            result ^= AES_IRREDUCIBLE_POLYNOMIAL;
        }
    }
    round++;
    return result;
}
