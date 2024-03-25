#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

int ilog2_v1(uint32_t i)
{
    uint32_t log = -1;
    while (i) {
        i >>= 1;
        log++;
    }
    return log;
}

static int ilog2_v2(uint32_t i)
{
    uint32_t result = 0;
    while (i >= 65536) {
        result += 16;
        i >>= 16;
    }
    while (i >= 256) {
        result += 8;
        i >>= 8;
    }
    while (i >= 16) {
        result += 4;
        i >>= 4;
    }
    while (i >= 4) {
        result += 2;
        i >>= 2;
    }
    while (i >= 2) {
        result += 1;
        i >>= 1;
    }
    return result;
}

int ilog2_v3(uint32_t v)
{
    return (31 - __builtin_clz(v|1));
}

int ceil_ilog2(uint32_t x)
{
    uint32_t r, shift;

    x--;
    r = (x > 0xFFFF) << 4;                                                                                                                                    
    x >>= r;
    shift = (x > 0xFF) << 3;
    x >>= shift;
    r |= shift;
    shift = (x > 0xF) << 2;
    x >>= shift;
    r |= shift;
    shift = (x > 0x3) << 1;
    x >>= shift;
    return (r | shift | (x > 1) ) + 1;       
}

int main(){
    unsigned int binary = 15; // 0b1111
    int log = ilog2_v2(binary);
    printf("log value of %d : %d \n",binary,log);
}