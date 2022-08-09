// #include <stdio.h>
#include "bitReversal.h"
#define SWAP(a, b) temp=(a); (a) = (b); (b) = temp;

void bitReversal(Cpx input[], int lenth)
{
    int i, j, m;
    Cpx temp;
    j = 0;
    for(i=0; i<lenth; i++)
    {
        if(j>i)
        {
            SWAP(input[j], input[i]);
            // printf("swap! (%i <-> %i)\n", i, j);
        }
        m = lenth>>1;
        while(m>=2 && j>=m)
        {
            j -= m;
            m >>=1;
        }
        j += m;
    }
}