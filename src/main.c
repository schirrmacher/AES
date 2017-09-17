
#include <stdio.h>
#include "./developer-utils/printing.h"
#include "./aes-components/aes-constants.h"
#include "./aes-components/substitute.h"
#include "./aes-components/shift-rows.h"
#include "./aes-components/mix-columns.h"
#include "./aes-components/key-addition.h"

int main(int argc, const char * argv[]) {
    
    uint32_t key[4] = {
        0x2b7e1516, 0x28aed2a6, 0xabf71588, 0x09cf4f3c
    };
    
    uint32_t state[4] = {
        0x6bc1bee2, 0x2e409f96, 0xe93d7e11, 0x7393172a
    };
    
    add_round_key(state, key);
    
    for (int i = 1; i <= 9; i++) {
        substitute(state);
        shift_rows(state);
        mix_columns(state);
        add_round_key(state, key);
    }
    
    substitute(state);
    shift_rows(state);
    add_round_key(state, key);
    
    print_state(state, HEX);
    
    return 0;
}
