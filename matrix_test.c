#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "matrix.h"

bool test(void)
{
    struct matrix
        a = newMatrix(3, 2),
        b = newMatrix(2, 1),
        res_ber = newMatrix(3, 1),
        res_real = newMatrix(3, 1);

    a.mat[0][0] = 1; a.mat[0][1] = 2;
    a.mat[1][0] = 3; a.mat[1][1] = 4;
    a.mat[2][0] = 5; a.mat[2][1] = 1;

    b.mat[0][0] = 2;
    b.mat[1][0] = 4;

    res_real.mat[0][0] = 10;
    res_real.mat[1][0] = 22;
    res_real.mat[2][0] = 14;

    res_ber = multiplyMatrix(&a, &b);

    printf("a:\n"); printMatrix(&a);
    printf("b:\n"); printMatrix(&b);
    printf("res_ber:\n"); printMatrix(&res_ber);
    printf("res_real:\n"); printMatrix(&res_real);

    if (res_ber.m != res_real.m || res_ber.n != res_real.n)
    {
        return false;
    }
    for (int n = 0; n < res_real.n; n++)
    {
        for (int m = 0; m < res_real.m; m++)
        {
            if (res_ber.mat[n][m] != res_real.mat[n][m])
            {
                return false;
            }
        }
    }
    return true;
}
int main(int argc, char const *argv[])
{
    bool a = test();
    printf("%s\n", a ? "test bestanden" : "test failed");
    return 0;
}
