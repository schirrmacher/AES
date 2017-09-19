
#ifndef substitute_h
#define substitute_h

#include <stdio.h>
#include <stdint.h>
#include "aes-constants.h"

extern uint8_t substitutes[256];

void substitute(uint8_t state[AES_KEY_WORDS][AES_WORD_BYTES]);

#endif /* substitute_h */
