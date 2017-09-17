
#ifndef mix_columns_h
#define mix_columns_h

#include <stdio.h>
#include <stdint.h>
#include "aes-constants.h"

void mix_columns(uint32_t state[AES_STATE_MATRIX_SPAN]);

#endif /* mix_columns_h */
