
#include "h-function.h"
#include "../substitute.h"


void h(word word) {
    for(int i = 0; i < AES_WORD_BYTES; i++) {
        word[i] = substitutes[word[i]];
    }
}
