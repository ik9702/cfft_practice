#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../Complex/Complex.h"



Cpx* fft(Cpx input[], int lenth, int flag);
Cpx* ifft(Cpx input[], int lenth, int flag);

void dataProcess(float input[], Cpx *output, int lenth);



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


    Cpx *res = fft(&cinput[0], 512, 1);
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



    Cpx *recov = ifft(&res[0], 512, 1);
    for(int i=0; i<512; i++)
    {
        output[i] = recov[i].real;
        output[i+512] = recov[i].imag;
    }
    file = fopen("../bin/recover.bin", "wb");
    for(int i=0; i<1024; i++)
    {
        fwrite(&output[i], sizeof(float), 1, file);
    }
    fclose(file);






    printf("it works");
    return 0;
}



Cpx *fft(Cpx input[], int lenth, int flag)
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
    E = fft(E, D_lth, 0);
    O = fft(O, D_lth, 0);

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
    if(flag != 1)
        free(input);
    return output;
}







Cpx *ifft(Cpx input[], int lenth, int flag)
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
    E = ifft(E, D_lth, 0);
    O = ifft(O, D_lth, 0);

    for(int i=0; i<D_lth; i++)
    {
        Cpx w;
        compInit(&w, (float)cos(i * -2 * pi / lenth), (float)sin(i * -2 * pi/lenth));
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





void dataProcess(float input[], Cpx output[], int lenth)
{
    for(int i=0; i<lenth; i++)
    {
        compInit(&output[i], input[i], 0);
    }
}