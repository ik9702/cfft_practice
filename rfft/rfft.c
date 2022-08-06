#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define pi 3.14159265358979


typedef struct _Cpx{
    float real;
    float imag;
} Cpx;

Cpx* fft(Cpx input[],int lenth);
void compInit(Cpx* input, float real, float imag);
void dataProcess(float input[], Cpx *output, int lenth);
Cpx cSum(Cpx *x, Cpx *y);
Cpx cSub(Cpx *x, Cpx *y);
Cpx cMul(Cpx *x, Cpx *y);




int main()
{
    float smp[512];
    char buff[256];
    FILE *file;
    sprintf(buff, "%s","../bin/input.bin");
    file=fopen(buff, "rb");
    fread(&(smp[0]), sizeof(float), 512, file);
    fclose(file);

    Cpx cinput[512];
    dataProcess(&smp[0], &cinput[0], 512);


    Cpx *res = fft(&cinput[0], 512);

    float output[1024];

    for(int i=0; i<512; i++)
    {
        output[i] = res[i].real;
        output[i+512] = res[i].imag;
    }

    file = fopen("../bin/output.bin", "wb");
    for(int i=0; i<1024; i++)
    {
        fwrite(&output[i], sizeof(float), 1, file);
    }
    fclose(file);
    printf("it works");
    return 0;
}



Cpx *fft(Cpx input[], int lenth)
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
    E = fft(E, D_lth);
    O = fft(O, D_lth);

    for(int i=0; i<D_lth; i++)
    {
        Cpx w;
        compInit(&w, (float)cos(i * 2 * pi / lenth), (float)sin(i * 2*pi/lenth));
        Cpx wO = cMul(&w, &O[i]);
        output[i] = cSum(&E[i], &wO);
        output[i+D_lth] = cSub(&E[i], &wO);
    }
    free(E);
    free(O);
    if(lenth != 512)
        free(input);
    return output;
}

Cpx *ifft(Cpx input[], int lenth)
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
        O[i] = input[i*2 + 1];
    }
    E = fft(E, D_lth);
    O = fft(O, D_lth);

    for(int i=0; i<D_lth; i++)
    {
        Cpx w;
        compInit(&w, (float)cos(i * 2 * pi / lenth), (float)sin(i * 2*pi/lenth));
        Cpx wO = cMul(&w, &O[i]);
        output[i] = cSum(&E[i], &wO);
        output[i+D_lth] = cSub(&E[i], &wO);
    }
    free(E);
    free(O);
    if(lenth != 512)
        free(input);
    return output;
}




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


void dataProcess(float input[], Cpx output[], int lenth)
{
    for(int i=0; i<lenth; i++)
    {
        compInit(&output[i], input[i], 0);
    }
}