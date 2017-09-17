
#include <stdio.h>
#include "./developer-utils/printing.h"
#include "./aes-components/aes-constants.h"
#include "./aes-components/substitute.h"
#include "./aes-components/shift-rows.h"
#include "./aes-components/mix-columns.h"
#include "./aes-components/key-addition.h"

int main(int argc, const char * argv[]) {
    
    uint32_t plaintext[4] = { 0x2B28AB09, 0x7EBEF7CF, 0x15D2154F, 0x16A6883C };
    uint32_t key[4] = { 0x00000008, 0x00000004, 0x00000002, 0x00000001 };
    
    
    
    return 0;
}
