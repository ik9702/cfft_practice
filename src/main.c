#include <stdio.h>
#include "main.h"

int main()
{
    float smp[512];
    char buff[256];
    FILE *file;
    sprintf(buff, "%s","bin/input.bin");
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

    file = fopen("bin/output.bin", "wb");
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
    file = fopen("bin/recover.bin", "wb");
    for(int i=0; i<1024; i++)
    {
        fwrite(&output[i], sizeof(float), 1, file);
    }
    fclose(file);


    printf("it works");
    return 0;
}