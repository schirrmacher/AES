
#include "./shift-rows.h"
#include <limits.h>


unsigned char left_shift_bits_cyclically(unsigned char value_to_shift, const unsigned int shifts);

void shift_rows(unsigned char matrix[AES_MATRIX_COLUMNS][AES_MATRIX_COLUMNS]) {
    for (int row_index = 0; row_index < AES_MATRIX_ROWS; row_index++) {
        for (int column_index = 0; column_index < AES_MATRIX_COLUMNS; column_index++) {
            const unsigned char current_entry = matrix[row_index][column_index];
            unsigned char shifted_entry = 0;
            switch (row_index) {
                case 0:
                shifted_entry = left_shift_bits_cyclically(current_entry, 0);
                break;
                case 1:
                shifted_entry = left_shift_bits_cyclically(current_entry, 1);
                break;
                case 2:
                shifted_entry = left_shift_bits_cyclically(current_entry, 2);
                break;
                case 3:
                shifted_entry = left_shift_bits_cyclically(current_entry, 3);
                break;
            }
            matrix[row_index][column_index] = shifted_entry;
        }
    }
}

unsigned char left_shift_bits_cyclically(unsigned char value_to_shift, const unsigned int shifts) {
    const int normalized_shifts = shifts % CHAR_BIT;
    const char shifted_value = value_to_shift << normalized_shifts;
    const char overflow = value_to_shift >> (CHAR_BIT - normalized_shifts);
    return shifted_value | overflow;
}
