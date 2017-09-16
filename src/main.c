
#include <stdio.h>
#include "./developer-utils/printing.h"
#include "./aes-components/aes-constants.h"
#include "./aes-components/substitute.h"
#include "./aes-components/shift-rows.h"
#include "./aes-components/mix-columns.h"
#include "./aes-components/key-schedule/g-function.h"
#include "key-schedule.h"

int main(int argc, const char * argv[]) {
    
    uint32_t block[4] = { 0x2B28AB09, 0x7EBEF7CF, 0x15D2154F, 0x16A6883C };
    uint32_t key[4] = { 0x00000008, 0x00000004, 0x00000002, 0x00000001 };
    
    printf("Key:");
    print_block(key, HEX);
    
    printf("Plaintext:");
    print_block(block, HEX);
    
    printf("Substitute:");
    substitute(block);
    print_block(block, HEX);
    
    printf("Shift:");
    shift_rows(block);
    print_block(block, HEX);
    
    printf("Mix:");
    mix_columns(block);
    print_block(block, HEX);
    
    // KEY SCHEDULE
    uint32_t round_key[4];
    
    printf("Round-key 0:");
    get_round_key(key, round_key);
    print_block(round_key, HEX);
    
    printf("Round-key 1:");
    get_round_key(key, round_key);
    print_block(round_key, HEX);
    
    return 0;
}
