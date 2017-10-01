
#include <assert.h>
#include <inttypes.h>
#include "./aes-components/aes.h"


static void print_block(block block);

int main(int argc, const char * argv[]) {
    
    key key = {
        0x603deb10, 0x15ca71be, 0x2b73aef0, 0x857d7781, 0x1f352c07, 0x3b6108d7, 0x2d9810a3, 0x0914dff4
    };
    
    block plaintext = {
        0xae2d8a57, 0x1e03ac9c, 0x9eb76fac, 0x45af8e51
    };
    
    block expected = {
        0x591ccb10, 0xd410ed26, 0xdc5ba74a, 0x31362870
    };
    
    block result;
    aes_256_encrypt_block(plaintext, key, result);
    
    printf("Expected:");
    print_block(expected);
    
    printf("Actual:");
    print_block(result);
    
    for (int i = 0; i < 4; i++) {
        if (result[i] != expected[i]) {
            printf("❌ Test failed.\n\n");
        }
        assert(result[i] == expected[i]);
    }
    
    printf("✅ Test succeeded!\n\n");
    
    return 0;
}

static void print_block(block block) {
    printf("\n");
    for (int i = 0; i < 4; i++) {
        printf("%08" PRIx32 " ", block[i]);
    }
    printf("\n\n");
}
