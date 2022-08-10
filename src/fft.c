#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fft.h"
#include <string.h>

#define pi 3.14159265358979323846


Cpx *R_fft(Cpx input[], int lenth, int flag)
{
    if(lenth == 1)
        return input;
    Cpx *output;
    output = (Cpx *)(malloc(lenth * sizeof(Cpx)));
    int D_lth = lenth>>1;
    Cpx *E, *O;
    E = (Cpx*)(malloc(D_lth*sizeof(Cpx)));
    O = (Cpx*)(malloc(D_lth*sizeof(Cpx)));
    for(int i=0; i<D_lth; i++)
    {
        E[i] = input[i*2];
        O[i] = input[i*2 +1];
    }
    E = R_fft(E, D_lth, 0);
    O = R_fft(O, D_lth, 0);

    for(int i=0; i<D_lth; i++)
    {
        Cpx w;
        compInit(&w, (float)cos(i * 2 * (float)pi / lenth), (float)sin(i * 2*(float)pi/lenth));
        Cpx wO = cMul(&w, &O[i]);
        output[i] = cSum(&E[i], &wO);
        output[i+D_lth] = cSub(&E[i], &wO);
    }
    free(E);
    free(O);
    if(flag != 1)
        free(input);
    return output;
}

Cpx *R_ifft(Cpx input[], int lenth, int flag)
{
    if(lenth == 1)
        return input;
    Cpx *output;
    output = (Cpx*)(malloc(lenth*sizeof(Cpx)));
    int D_lth = lenth>>1;
    Cpx *E, *O;
    E = (Cpx*)(malloc(D_lth*sizeof(Cpx)));
    O = (Cpx*)(malloc(D_lth*sizeof(Cpx)));
    for(int i=0; i<D_lth; i++)
    {
        E[i] = input[i*2];
        O[i] = input[i*2 +1];
    }
    E = R_ifft(E, D_lth, 0);
    O = R_ifft(O, D_lth, 0);

    for(int i=0; i<D_lth; i++)
    {
        Cpx w;
        compInit(&w, (float)cos(i * -2 * (float)pi / lenth), (float)sin(i * -2 * (float)pi/lenth));
        Cpx wO = cMul(&w, &O[i]);
        output[i] = cSum(&E[i], &wO);
        output[i+D_lth] = cSub(&E[i], &wO);
    }
    free(E);
    free(O);
    if(flag != 1)
    {
        free(input);
    }
    else if(flag == 1)
    {
        for(int i=0; i<lenth; i++)
        {
            output[i].real /= lenth;
            output[i].imag /= lenth;
        }
    }
    return output;
}

Cpx *Radix2(Cpx input[], const int lenth)
{
    int m, mm;
    Cpx *output, w, E, O, Ow;
    output = (Cpx*)(calloc(lenth, sizeof(Cpx)));
    memcpy(output, &input[0] ,sizeof(Cpx)*lenth);
    bitReversal(output, lenth);
    m = 2;
    while(m <= lenth)
    {
        // printf("size : %i", m);
        // puts("error1");
        for(int i=0; i<lenth; i += m)
        {
            mm = m>>1;
            // puts("error2");
            for(int j=0; j<mm; j++)
            {
                compInit(&w, (float)cos(j * 2 * (float)pi / m), (float)sin(j * 2*(float)pi/m));
                E = output[i + j];
                O = output[i + j + mm];
                Ow = cMul(&w, &O);

                output[i + j] = cSum(&E, &Ow);
                output[i + j + mm] = cSub(&E, &Ow);
            }
        }
        m <<= 1;
    }
    return output;
}

Cpx *i_Radix2(Cpx input[], const int lenth)
{
    int m, mm;
    Cpx *output, w, Ow;
    output = (Cpx*)(calloc(lenth, sizeof(Cpx)));
    memcpy(output, &input[0] ,sizeof(Cpx)*lenth);
    bitReversal(output, lenth);
    m = 2;
    while(m <= lenth)
    {

        for(int i=0; i<lenth; i += m)
        {
            mm = m>>1;
            // puts("error2");
            for(int j=0; j<mm; j++)
            {
        
                compInit(&w, (float)cos(j * 2 * (float)pi / m), (float)sin(-1 * j * 2*(float)pi/m));
                Cpx E = output[i + j];
                Cpx O = output[i + j + mm];
                Cpx Ow = cMul(&w, &O);

                output[i + j] = cSum(&E, &Ow);
                output[i + j + mm] = cSub(&E, &Ow);
            }
        }
        m <<= 1;
    }
    for(int i=0; i<lenth; i++)
    {
        output[i].real /= lenth;
        output[i].imag /= lenth;
    }
    return output;
}

