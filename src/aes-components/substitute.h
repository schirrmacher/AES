
#ifndef substitute_h
#define substitute_h

#include <stdio.h>
#include "aes-constants.h"

extern uint8_t substitutes[256];

void substitute(uint32_t block[AES_STATE_MATRIX_SPAN]);

#endif /* substitute_h */
