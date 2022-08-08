#include <stdio.h>
#include <math.h>

#define SWAP(a, b) temp=(a); (a) = (b); (b) = temp;
#define lth 16
void bitReversal(float input[], int lenth);

int main()
{

    return 0;
}




void bitReversal(float input[], int lenth)
{
    int i, j, m;
    float temp;
    j = 0;
    for(i=0; i<lenth; i++)
    {
        if(j>i)
        {
            SWAP(input[j], input[i]);
            printf("swap! (%i <-> %i)\n", i, j);
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