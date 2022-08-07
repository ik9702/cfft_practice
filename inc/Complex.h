#ifndef __COMPLEX_H
#define __COMPLEX_H

typedef struct _Cpx{
    float real;
    float imag;
} Cpx;

void compInit(Cpx* input, float real, float imag);
Cpx cSum(Cpx *x, Cpx *y);
Cpx cSub(Cpx *x, Cpx *y);
Cpx cMul(Cpx *x, Cpx *y);

#endif