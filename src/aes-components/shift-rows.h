
#ifndef shift_rows_h
#define shift_rows_h

#include <stdio.h>
#include "aes-constants.h"

void shift_rows(byte state[AES_STATE_SPAN][AES_STATE_SPAN]);

#endif /* shift_rows_h */
