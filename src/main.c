#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"

#define pi 3.14159265358979323846

// void export(float input[], int lenth, char* DIR);
// void import(float input[], int lenth, char* DIR);

void hann(int length, float input[]);
Cpx* stft(float input[], int length, int n_fft, int hop_length, float window[]);



int main()
{
    // float smp[512];
    // char buff[256];
    // FILE *file;
    // sprintf(buff, "%s","bin/input.bin");
    // file=fopen(buff, "rb");
    // fread(&(smp[0]), sizeof(float), 512, file);
    // fclose(file);


    // Cpx cinput[512];
    // RtoC(&smp[0], &cinput[0], 512);
    // //----------------------------------------------------

    // Cpx *res = Radix2(&cinput[0], 512);
    // float output[1024];
    // CtoR(res, &output[0], 512);

    // // //-------------------------------------------------

    // file = fopen("bin/export/output.bin", "wb");
    // for(int i=0; i<1024; i++)
    // {
    //     fwrite(&output[i], sizeof(float), 1, file);
    // }
    // fclose(file);

    // Cpx *recov = i_Radix2(&res[0], 512);
    
    // CtoR(recov, output, 512);
    // file = fopen("bin/export/recover.bin", "wb");
    // for(int i=0; i<1024; i++)
    // {
    //     fwrite(&output[i], sizeof(float), 1, file);
    // }
    // fclose(file);


    float smp[114958];
    char buff[256];
    FILE *file;
    sprintf(buff, "%s","bin/wavinput.bin");
    file=fopen(buff, "rb");
    fread(&(smp[0]), sizeof(float), 114958, file);
    fclose(file);

    // for(int i=0; i<114958; i++)
    // {
    //     printf("%f, ", smp[i]);
    // }


    float han_win[256];
    hann(256, han_win);
    
    // for(int i=0; i<256; i++)
    // {
    //     printf("%f, ", han_win[i]);
    // }

    Cpx* result = stft(smp, 114958, 256, 128, han_win);
    // float output[460288];
    // CtoR(result, &output[0], 230144);

    // for(int i=0; i<230145; i++)
    // {
    //     if(isinf(result[i].real))
    //         printf("nan \n");
    //     if(isinf(result[i].imag))
    //         printf("nan \n");
    // }

    file = fopen("bin/export/st.bin", "wb");
    for(int i=0; i<230144; i++)
    {
        fwrite(&result[i].real, sizeof(float), 1, file);
    }
        for(int i=0; i<230144; i++)
    {
        fwrite(&result[i].imag, sizeof(float), 1, file);
    }
    fclose(file);



    // // file = fopen("bin/export/st.bin", "wb");
    // // for(int i=0; i<460288; i++)
    // // {
    // //     fwrite(&out[i], sizeof(float), 1, file);
    // //     printf("%f, ", out[i]);
    // // }
    // // fclose(file);
    printf("it works");
    return 0;
}

void hann(int length, float input[])
{
    for(int i=0; i<length; i++)
    {
        input[i] = 0.5 * (1 - (float)cos(2 * (float)pi * i / (length)));
    }
}






Cpx* stft(float input[], int length, int n_fft, int hop_length, float window[])
{
    float *padded, *wave;
    Cpx *cp, *ft;
    padded = (float*)(calloc(length+n_fft, sizeof(float)));
    wave = (float*)(calloc(n_fft, sizeof(float)));
    cp = (Cpx*)(calloc(n_fft, sizeof(Cpx)));

    int time_point = 1 + (int)(length / hop_length);
    Cpx *stft;
    stft = (Cpx*)(calloc(time_point*n_fft, sizeof(Cpx)));    
    for(int i=0; i<length; i++)
    {
        padded[i + (n_fft>>1)] = input[i];        
    }

    for(int i=0; i<time_point; i++)
    {
        for(int j=0; j<n_fft; j++)
        {
            wave[j] = window[j] * padded[i*hop_length + j];
        }
        RtoC(&wave[0], &cp[0], n_fft);
        ft = Radix2(&cp[0], n_fft);
        for(int j=0; j<n_fft; j++)
        {
            stft[n_fft*i + j] = ft[j];
        }
        free(ft);
    }
free(padded);
free(wave);
free(cp);
return stft;
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