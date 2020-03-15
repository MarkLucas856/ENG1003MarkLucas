#include <stdio.h>
#include <stdlib.h>

int main()
{
    float x0 = 0.65, xnm1 =0, xn= 0.2 * xnm1 + 5;
    int n=0;
    printf("x%d= %f\n", n, x0);


    while((n<10)&&(xn-xnm1 > 0.001))
    {
        n++;
        xnm1 = x0;
        xn = 0.2 * xnm1 + 5; // the order of these is important!
        x0 = xn;
        printf("x%d= %f\n", n, xn);
    }

    printf("END");

    return 0;
}
