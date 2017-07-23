
#include <stdio.h>
#include "./developer-utils/printing.h"
#include "./aes-components/aes-constants.h"
#include "./aes-components/substitute.h"
#include "./aes-components/shift-rows.h"
#include "./aes-components/mix-columns.h"

#define ROWS AES_MATRIX_SPAN
#define COLUMNS AES_MATRIX_SPAN

int main(int argc, const char * argv[]) {
    unsigned char values[ROWS][COLUMNS] = {
        { 0x2B, 0x28, 0xAB, 0x09 },
        { 0x7E, 0xBE, 0xF7, 0xCF },
        { 0x15, 0xD2, 0x15, 0x4F },
        { 0x16, 0xA6, 0x88, 0x3C }
    };
    
    print_matrix(ROWS, COLUMNS, values, HEX);
    
    printf("Substitute:");
    substitute(values);
    print_matrix(ROWS, COLUMNS, values, HEX);
    
    printf("Shift:");
    shift_rows(values);
    print_matrix(ROWS, COLUMNS, values, HEX);
    
    printf("Mix:");
    mix_columns(values);
    print_matrix(ROWS, COLUMNS, values, HEX);
    
    return 0;
}
