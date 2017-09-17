
#ifndef shift_rows_h
#define shift_rows_h

#include <stdio.h>
#include "aes-constants.h"

void shift_rows(uint32_t state[AES_STATE_MATRIX_SPAN]);

#endif /* shift_rows_h */
