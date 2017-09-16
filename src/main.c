
#include <stdio.h>
#include "./developer-utils/printing.h"
#include "./aes-components/aes-constants.h"
#include "./aes-components/substitute.h"
#include "./aes-components/shift-rows.h"
#include "./aes-components/mix-columns.h"
#include "./aes-components/key-schedule/g-function.h"
#include "key-schedule.h"

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
    
    // KEY SCHEDULE
    
    uint32_t key[4] = { 0x00000008, 0x00000004, 0x00000002, 0x00000001 };
    uint32_t round_key[4];
    
    get_round_key(key, round_key);
    for (int i = 0; i < 4; i++) {
        print_hex_uint32(round_key[i]);
        printf("\n");
    }
    
    printf("\n");
    
    get_round_key(key, round_key);
    for (int i = 0; i < 4; i++) {
        print_hex_uint32(round_key[i]);
        printf("\n");
    }
    
    return 0;
}
