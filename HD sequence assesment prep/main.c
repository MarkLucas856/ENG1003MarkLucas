#include <stdio.h>
#include <stdlib.h>
#include<math.h> // add this math function for powers
int main()
{
    float x0 = 1.47; // xnm2
    float x1 = 0.14; //xnm1
    float xn = 0.8* x1 - 0.2 * x0;
    int n = 0; // counter
    float a = pow(10, 10); // a = 10^10

    printf("x%d= %f\n", n, x0);
    n++;
    printf("x%d= %f\n", n, x1);
    n++;

    while((n<11)&&(xn<a))
    {
        xn = 0.8* x1 - 0.2 * x0;
        printf("x%d= %f\n", n, xn);
        x0 = x1;
        x1 = xn;
        n++;
    }
    return 0;
}
