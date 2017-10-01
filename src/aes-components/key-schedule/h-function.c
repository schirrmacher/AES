
#include "h-function.h"
#include "../substitute.h"


void h(word word_ref) {
    for(int i = 0; i < AES_WORD_BYTES; i++) {
        word_ref[i] = substitutes[word_ref[i]];
    }
}
