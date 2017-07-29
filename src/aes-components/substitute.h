
#ifndef substitute_h
#define substitute_h

#include <stdio.h>
#include "aes-constants.h"

void substitute(uint8_t block[AES_STATE_MATRIX_SPAN][AES_STATE_MATRIX_SPAN]);

#endif /* substitute_h */
