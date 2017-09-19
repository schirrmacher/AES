
#ifndef shift_rows_h
#define shift_rows_h

#include <stdio.h>
#include <stdint.h>
#include "aes-constants.h"

void shift_rows(uint8_t state[AES_KEY_WORDS][AES_WORD_BYTES]);

#endif /* shift_rows_h */
