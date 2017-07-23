
#include "./shift-rows.h"
#include <string.h>
#include <limits.h>


void shift_rows(aes_byte block[AES_BLOCK_MATRIX_SPAN][AES_BLOCK_MATRIX_SPAN]) {
    
    aes_byte result[AES_BLOCK_MATRIX_SPAN][AES_BLOCK_MATRIX_SPAN];
    
    for (int row_index = 0; row_index < AES_BLOCK_MATRIX_SPAN; row_index++) {
        for (int column_index = 0; column_index < AES_BLOCK_MATRIX_SPAN; column_index++) {
            
            int shifted_column_index = column_index;
            
            switch (row_index) {
                case 0:
                    // don't shift
                    break;
                case 1:
                    // here one left shift: column_index - 1 + 4 mod 4 <=> column_index + 3 mod 4
                    shifted_column_index = (column_index + 3) % AES_BLOCK_MATRIX_SPAN;
                    break;
                case 2:
                    shifted_column_index = (column_index + 2) % AES_BLOCK_MATRIX_SPAN;
                    break;
                case 3:
                    shifted_column_index = (column_index + 1) % AES_BLOCK_MATRIX_SPAN;
                    break;
            }
            const aes_byte current_entry = block[row_index][column_index];
            result[row_index][shifted_column_index] = current_entry;
        }
    }
    
    for(int i = 0; i < AES_BLOCK_MATRIX_SPAN; i++) {
        memcpy(&block[i], &result[i], sizeof(result[0]));
    }
    
}
