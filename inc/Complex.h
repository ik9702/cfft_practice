#include <stdio.h>

#define pi 3.14159265358979

typedef struct _Cpx{
    float real;
    float imag;
} Cpx;

void compInit(Cpx* input, float real, float imag);
Cpx cSum(Cpx *x, Cpx *y);
Cpx cSub(Cpx *x, Cpx *y);
Cpx cMul(Cpx *x, Cpx *y);