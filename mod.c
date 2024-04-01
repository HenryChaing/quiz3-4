#include <stdint.h>
#include <stdio.h>

void divmod_10(uint32_t in, uint32_t *div, uint32_t *mod)
{
    uint32_t x = (in | 1) - (in >> 2); /* div = in/10 ==> div = 0.75*in/8 */
    uint32_t q = (x >> 4) + x;
    x = q;
    q = (q >> 8) + x;
    q = (q >> 8) + x;
    q = (q >> 8) + x;
    q = (q >> 8) + x;

    *div = (q >> 3);
    *mod = in - ((q & ~0x7) + (*div << 1));
    // printf("(%u,%u)\n",*div,*mod);   
}

uint32_t mod5( uint32_t a ) {
    a = (a >> 16) + (a & 0xFFFF); /* maximun value: 0x1FFFE */
    a = (a >>  8) + (a & 0xFF);   /* maximun value: 0x2FD */
    a = (a >>  4) + (a & 0xF);    /* maximun value: 0x3C */
    a = (a >>  4) + (a & 0xF);    /* maximun value: 0xF */
    if(a<5)return a;
    if(a<10)return a-5;
    return a-10;
}

uint32_t mod15( uint32_t a ) {
    a = (a >> 16) + (a & 0xFFFF); /* maximun value: 0x1FFFE */
    a = (a >>  8) + (a & 0xFF);   /* maximun value: 0x2FD */
    a = (a >>  4) + (a & 0xF);    /* maximun value: 0x3C */
    return (a >>  4) + (a & 0xF);
}

int main(){

    unsigned div, mod;
    divmod_10(195, &div, &mod);
    printf("%d\n",mod15(5));
   
}