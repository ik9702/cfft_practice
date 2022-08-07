#include <stdio.h>
#include "complex.h"


void compInit(Cpx* input, float real, float imag)
{
    input->real = real;
    input->imag = imag;
}

Cpx cSum(Cpx *x, Cpx *y)
{
    Cpx output;
    output.real = x->real + y->real;
    output.imag = x->imag + y->imag;
    return output;
}

Cpx cSub(Cpx *x, Cpx *y)
{
    Cpx output;
    output.real = x->real - y->real;
    output.imag = x->imag - y->imag;
    return output;
}


Cpx cMul(Cpx *x, Cpx *y)
{
    Cpx output;
    output.real = x->real * y->real - x->imag * y->imag;
    output.imag = x->real * y->imag + x->imag * y->real;
    return output;
}