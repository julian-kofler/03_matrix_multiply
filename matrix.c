#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct matrix
{ // Matrix mit n Spalten und m Zeilen
    int **mat;
    int n;
    int m;
};
struct matrix newMatrix(int n, int m)
{
    struct matrix ret = {
        .mat = (int **)calloc(m, sizeof(int *)),
        .n = n,
        .m = m,
    };
    for (int i = 0; i < m; i++)
    {
        ret.mat[i] = (int *)calloc(n, sizeof(int));
    }
    return ret;
};
struct matrix multiplyMatrix(struct matrix *a, struct matrix *b)
{
    struct matrix ret = newMatrix(a->m, b->n);
    for (int i = 0; i < a->m; i++)
    {
        for (int j = 0; j < b->n; j++)
        {
            int sum = 0;
            for (int k = 0; k < a->n; k++)
            {
                sum += a->mat[i][k] * b->mat[k][j];
            }
            ret.mat[i][j] = sum;
        }
    }
}
void printMatrix(struct matrix *mat)
{
    for (int n = 0; n < mat->n; n++)
    {
        for (int m = 0; m < mat->m; m++)
        {
            printf("%d\t",mat->mat[n][m]);
        }
        printf("\n");
    }
}
bool test(void)
{
    struct matrix
        a = newMatrix(3, 2),
        b = newMatrix(2, 1),
        res_ber = newMatrix(3, 1),
        res_real = newMatrix(3, 1);

    a.mat[0][0] = 1; a.mat[1][0] = 2;
    a.mat[0][1] = 3; a.mat[1][1] = 4;
    a.mat[0][2] = 5; a.mat[1][2] = 1;

    b.mat[0][0] = 2;
    b.mat[0][1] = 4;

    res_real.mat[0][0] = 10;
    res_real.mat[0][1] = 22;
    res_real.mat[0][2] = 14;

    res_ber = multiplyMatrix(&a, &b);

    printf("a:\n"); printMatrix(&a);
    printf("b:\n"); printMatrix(&b);
    printf("res_ber:\n"); printMatrix(&res_ber);
    printf("res_real:\n"); printMatrix(&res_real);

    if(res_ber.m != res_real.m || res_ber.n != res_real.n)
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
    printf("%s\n",a?"test bestanden":"test failed");
    return 0;
}
