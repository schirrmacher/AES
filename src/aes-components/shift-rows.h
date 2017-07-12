
#ifndef shift_rows_h
#define shift_rows_h

#include <stdio.h>
#include "aes-constants.h"

void shift_rows(unsigned char matrix[AES_MATRIX_COLUMNS][AES_MATRIX_ROWS]);

#endif /* shift_rows_h */
