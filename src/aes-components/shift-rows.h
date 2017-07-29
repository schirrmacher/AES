
#ifndef shift_rows_h
#define shift_rows_h

#include <stdio.h>
#include "aes-constants.h"

void shift_rows(uint8_t block[AES_STATE_MATRIX_SPAN][AES_STATE_MATRIX_SPAN]);

#endif /* shift_rows_h */
