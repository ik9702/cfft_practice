#ifndef __RFFT_H
#define __RFFT_H

#include "complex.h"
Cpx* R_fft(Cpx input[], int lenth, int flag);
Cpx* R_ifft(Cpx input[], int lenth, int flag);

#endif