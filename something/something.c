#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define pi 3.14159265358979


typedef struct
{
    float real;
    float imag;
}complex;

complex* fft(complex input[],int lenth);
void compInit(complex* input, float real, float imag);
void dataProcess(float input[], complex *output, int lenth);
complex cSum(complex *x, complex *y);
complex cSub(complex *x, complex *y);
complex cMul(complex *x, complex *y);




int main()
{
    float smp[512];
    char buff[256];
    FILE *file;
    sprintf(buff, "%s","../bin/input.bin");
    file=fopen(buff, "rb");
    fread(&(smp[0]), sizeof(float), 512, file);
    fclose(file);

    complex cinput[512];
    dataProcess(&smp[0], &cinput[0], 512);


    fft(&cinput[0], 512);

    file = fopen("../bin/output.bin", "wb");
    for(int i=0; i<512; i++)
    {
        fwrite(&cinput[i].real, sizeof(float), 1, file);
        fwrite(&cinput[i].imag, sizeof(float), 1, file);
    }
    fclose(file);


    printf("it works");
    return 0;
}



void fft(complex input[], complex output[], int lenth)
{
    if(lenth <= 1)
        return;

    output = (complex*)(malloc(lenth*sizeof(complex)));
    int D_lth = lenth>>1;
    complex *E, *O;
    E = (complex*)(malloc(D_lth*sizeof(complex)));
    O = (complex*)(malloc(D_lth*sizeof(complex)));
    for(int i=0; i<D_lth; i++)
    {
        E[i] = input[i*2];
        O[i] = input[i*2 +1];
    }
    fft(E, D_lth);
    fft(O, D_lth);

    for(int i=0; i<D_lth; i++)
    {
        complex w;
        compInit(&w, (float)cos(i * 2 * pi / lenth), (float)sin(i * 2*pi/lenth));
        complex wO = cMul(&w, &O[i]);
        output[i] = cSum(&E[i], &wO);
        output[i+D_lth] = cSub(&E[i], &wO);
    }
    free(E);
    free(O);
    if(lenth != 512)
        free(input);
    return output;
}


void compInit(complex* input, float real, float imag)
{
    input->real = real;
    input->imag = imag;
}



complex cSum(complex *x, complex *y)
{
    complex output;
    output.real = x->real + y->real;
    output.imag = x->imag + y->imag;
    return output;
}

complex cSub(complex *x, complex *y)
{
    complex output;
    output.real = x->real - y->real;
    output.imag = x->imag - y->imag;
    return output;
}


complex cMul(complex *x, complex *y)
{
    complex output;
    output.real = x->real * y->real - x->imag * y->imag;
    output.imag = x->real * y->imag + x->imag * y->real;
    return output;
}


void dataProcess(float input[], complex output[], int lenth)
{
    for(int i=0; i<lenth; i++)
    {
        compInit(&output[i], input[i], 0);
    }
}