
#include "./shift-rows.h"
#include <string.h>
#include <limits.h>


void shift_rows(unsigned char matrix[AES_MATRIX_COLUMNS][AES_MATRIX_COLUMNS]) {
    
    unsigned char result[AES_MATRIX_COLUMNS][AES_MATRIX_COLUMNS];
    
    for (int row_index = 0; row_index < AES_MATRIX_ROWS; row_index++) {
        for (int column_index = 0; column_index < AES_MATRIX_COLUMNS; column_index++) {
            
            int shifted_column_index = column_index;
            
            switch (row_index) {
                case 0:
                    // don't shift
                    break;
                case 1:
                    // here one left shift: column_index - 1 + 4 mod 4 <=> column_index + 3 mod 4
                    shifted_column_index = (column_index + 3) % AES_MATRIX_COLUMNS;
                    break;
                case 2:
                    shifted_column_index = (column_index + 2) % AES_MATRIX_COLUMNS;
                    break;
                case 3:
                    shifted_column_index = (column_index + 1) % AES_MATRIX_COLUMNS;
                    break;
            }
            const unsigned char current_entry = matrix[row_index][column_index];
            result[row_index][shifted_column_index] = current_entry;
        }
    }
    
    for(int i = 0; i < AES_MATRIX_ROWS; i++) {
        memcpy(&matrix[i], &result[i], sizeof(result[0]));
    }
    
}
