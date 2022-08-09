#ifndef __FFT_H
#define __FFT_H

#include "complex.h"
#include "bitReversal.h"
Cpx* R_fft(Cpx input[], int lenth, int flag);
Cpx* R_ifft(Cpx input[], int lenth, int flag);
Cpx *Radix2(Cpx input[], const int lenth);
Cpx *i_Radix2(Cpx input[], const int lenth);



#endif