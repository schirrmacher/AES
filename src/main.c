
#include <stdio.h>
#include "./developer-utils/printing.h"
#include "./aes-components/aes-constants.h"

#define ROWS AES_MATRIX_ROWS
#define COLUMNS AES_MATRIX_COLUMNS

int main(int argc, const char * argv[]) {
    unsigned char values[ROWS][COLUMNS] = {
        { 0x2B, 0x28, 0xAB, 0x09 },
        { 0x7E, 0xBE, 0xF7, 0xCF },
        { 0x15, 0xD2, 0x15, 0x4F },
        { 0x16, 0xA6, 0x88, 0x3C }
    };
    print_matrix(ROWS, COLUMNS, values, HEX);
    return 0;
}
