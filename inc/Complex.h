#ifndef __COMPLEX_H
#define __COMPLEX_H

typedef struct _Cpx{
    float real;
    float imag;
} Cpx;
void compInit(Cpx* input, float real, float imag);
void RtoC(float input[], Cpx output[], int lenth);
void CtoR(Cpx input[], float output[], int lenth);
Cpx cSum(Cpx *x, Cpx *y);
Cpx cSub(Cpx *x, Cpx *y);
Cpx cMul(Cpx *x, Cpx *y);

#endif