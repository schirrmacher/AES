
#include <assert.h>
#include <inttypes.h>
#include "./aes-components/aes.h"


static void test_equality(block *expected, block *actual, size_t size);
static void compare_blocks(block blockA, block blockB);

int main(int argc, const char * argv[]) {
    
    key key = {
        0x603deb10, 0x15ca71be, 0x2b73aef0, 0x857d7781, 0x1f352c07, 0x3b6108d7, 0x2d9810a3, 0x0914dff4
    };
    
    block plaintext[4] = {
        0x6bc1bee2, 0x2e409f96, 0xe93d7e11, 0x7393172a,
        0xae2d8a57, 0x1e03ac9c, 0x9eb76fac, 0x45af8e51,
        0x30c81c46, 0xa35ce411, 0xe5fbc119, 0x1a0a52ef,
        0xf69f2445, 0xdf4f9b17, 0xad2b417b, 0xe66c3710
    };
    
    block ciphertext[4] = {
        0xf3eed1bd, 0xb5d2a03c, 0x064b5a7e, 0x3db181f8,
        0x591ccb10, 0xd410ed26, 0xdc5ba74a, 0x31362870,
        0xb6ed21b9, 0x9ca6f4f9, 0xf153e7b1, 0xbeafed1d,
        0x23304b7a, 0x39f9f3ff, 0x067d8d8f, 0x9e24ecc7
    };
    
    printf("Encryption Test:");
    block encryption_data[4] = {
        0x6bc1bee2, 0x2e409f96, 0xe93d7e11, 0x7393172a,
        0xae2d8a57, 0x1e03ac9c, 0x9eb76fac, 0x45af8e51,
        0x30c81c46, 0xa35ce411, 0xe5fbc119, 0x1a0a52ef,
        0xf69f2445, 0xdf4f9b17, 0xad2b417b, 0xe66c3710
    };
    aes_256_encrypt(key, encryption_data, 4, ECB);
    test_equality(ciphertext, encryption_data, 4);
    
    printf("Decryption Test:");
    block decryption_data[4] = {
        0xf3eed1bd, 0xb5d2a03c, 0x064b5a7e, 0x3db181f8,
        0x591ccb10, 0xd410ed26, 0xdc5ba74a, 0x31362870,
        0xb6ed21b9, 0x9ca6f4f9, 0xf153e7b1, 0xbeafed1d,
        0x23304b7a, 0x39f9f3ff, 0x067d8d8f, 0x9e24ecc7
    };
    aes_256_decrypt(key, decryption_data, 4, ECB);
    test_equality(plaintext, decryption_data, 4);
    
    return 0;
}

static void test_equality(block *expected, block *actual, size_t size) {
    printf("\n");
    for (int i = 0; i < size; i++) {
        compare_blocks(expected[i], actual[i]);
    }
}

static void compare_blocks(block blockA, block blockB) {
    int test_failed = 0;
    printf("   \n");
    for (int i = 0; i < 4; i++) {
        if (blockA[i] != blockB[i])
            test_failed = 1;
        printf("%08" PRIx32 " ", blockA[i]);
    }
    printf("== \n");
    for (int i = 0; i < 4; i++) {
        printf("%08" PRIx32 " ", blockB[i]);
    }
    if (test_failed == 1)
        printf("❌\n\n");
    else
        printf("✅\n\n");
}
