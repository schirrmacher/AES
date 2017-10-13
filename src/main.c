
#include "tests.h"
#include <assert.h>


int main(int argc, const char * argv[]) {
    
    assert(0 == test_cbc_mode());
    assert(0 == test_ecb_mode());
    assert(0 == test_padding());
    
    return 0;
}
