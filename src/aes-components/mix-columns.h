
#ifndef mix_columns_h
#define mix_columns_h

#include <stdio.h>
#include "aes-constants.h"

void mix_columns(unsigned char matrix[AES_MATRIX_SPAN][AES_MATRIX_SPAN]);

#endif /* mix_columns_h */
