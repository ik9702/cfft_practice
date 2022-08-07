#ifndef __RFFT_H
#define __RFFT_H

#include "complex.h"
void dataProcess(float input[], Cpx output[], int lenth);
Cpx* fft(Cpx input[], int lenth, int flag);
Cpx* ifft(Cpx input[], int lenth, int flag);

#endif