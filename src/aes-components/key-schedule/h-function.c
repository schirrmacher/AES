
#include "h-function.h"
#include "../substitute.h"


void h(byte word[AES_WORD_BYTES]) {
    for(int i = 0; i < AES_WORD_BYTES; i++) {
        word[i] = substitutes[word[i]];
    }
}
