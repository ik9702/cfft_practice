#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"


void export(float input[], int lenth, char* DIR);
void import(float input[], int lenth, char* DIR);

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
    RtoC(&smp[0], &cinput[0], 512);
    //----------------------------------------------------

    Cpx *res = Radix2(&cinput[0], 512);
    float output[1024];
    CtoR(res, &output[0], 512);

    // //-------------------------------------------------

    file = fopen("bin/export/output.bin", "wb");
    for(int i=0; i<1024; i++)
    {
        fwrite(&output[i], sizeof(float), 1, file);
    }
    fclose(file);

    Cpx *recov = i_Radix2(&res[0], 512);
    
    CtoR(recov, output, 512);
    file = fopen("bin/export/recover.bin", "wb");
    for(int i=0; i<1024; i++)
    {
        fwrite(&output[i], sizeof(float), 1, file);
    }
    fclose(file);
    printf("it works");
    return 0;
}



// void import(float input[], int lenth, char* DIR)
// {
//     char buff[256];
//     FILE *file;
//     sprintf(buff, "%s","DIR");
//     file=fopen(buff, "rb");
//     fread(&(input[0]), sizeof(float), lenth, file);
//     fclose(file);     
// }

// void export(float input[], int lenth, char* DIR)
// {
//     char buff[256];
//     FILE *file;
//     file = fopen(DIR, "wb");
//     for(int i=0; i<lenth; i++)
//     {
//         fwrite(&(input[i]), sizeof(float), 1, file);
//     }
//     fclose(file); 
// }





// int main()
// {
//     float smp[512];
//     char buff[256];
//     FILE *file;
//     sprintf(buff, "%s","bin/input.bin");
//     file=fopen(buff, "rb");
//     fread(&(smp[0]), sizeof(float), 512, file);
//     fclose(file);

//     Cpx cinput[512];
//     RtoC(&smp[0], &cinput[0], 512);
//     Cpx *res = R_fft(&cinput[0], 512, 1);
//     float output[1024];
//     CtoR(&res[0], &output[0], 512);

//     file = fopen("bin/output.bin", "wb");
//     for(int i=0; i<1024; i++)
//     {
//         fwrite(&output[i], sizeof(float), 1, file);
//     }
//     fclose(file);



//     Cpx *recov = R_ifft(&res[0], 512, 1);
//     CtoR(recov, output, 512);
//     file = fopen("bin/recover.bin", "wb");
//     for(int i=0; i<1024; i++)
//     {
//         fwrite(&output[i], sizeof(float), 1, file);
//     }
//     fclose(file);


//     printf("it works");
//     return 0;
// }