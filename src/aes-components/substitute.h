
#ifndef substitute_h
#define substitute_h

#include <stdio.h>
#include "aes-constants.h"

void substitute(uint8_t block[AES_BLOCK_MATRIX_SPAN][AES_BLOCK_MATRIX_SPAN]);

#endif /* substitute_h */
