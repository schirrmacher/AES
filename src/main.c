
#include <stdio.h>
#include "./developer-utils/printing.h"
#include "./aes-components/aes-constants.h"
#include "./aes-components/substitute.h"
#include "./aes-components/shift-rows.h"
#include "./aes-components/mix-columns.h"
#include "./aes-components/key-schedule/g-function.h"

#define ROWS AES_STATE_MATRIX_SPAN
#define COLUMNS AES_STATE_MATRIX_SPAN

int main(int argc, const char * argv[]) {
    uint8_t block[ROWS][COLUMNS] = {
        0x2B, 0x28, 0xAB, 0x09,
        0x7E, 0xBE, 0xF7, 0xCF,
        0x15, 0xD2, 0x15, 0x4F,
        0x16, 0xA6, 0x88, 0x3C
    };
    
    print_block(ROWS, COLUMNS, block, HEX);
    
    printf("Substitute:");
    substitute(block);
    print_block(ROWS, COLUMNS, block, HEX);
    
    printf("Shift:");
    shift_rows(block);
    print_block(ROWS, COLUMNS, block, HEX);
    
    printf("Mix:");
    mix_columns(block);
    print_block(ROWS, COLUMNS, block, HEX);
    
    uint8_t test[4] = {
        0x00, 0x00, 0x00, 0x01
    };
    g(test);
    
    return 0;
}
