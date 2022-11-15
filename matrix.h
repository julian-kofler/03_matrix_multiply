#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct matrix // (m,n) Matrix mit n Spalten und m Zeilen
{
    float **mat;
    int m; // Zeilen
    int n; // Spalten
};
struct matrix newMatrix(int m, int n)
{
    struct matrix ret = {
        .mat = (float **)calloc(m, sizeof(float *)),
        .n = n,
        .m = m,
    };
    for (int i = 0; i < m; i++)
    {
        ret.mat[i] = (float *)calloc(n, sizeof(float));
    }
    return ret;
};
struct matrix multiplyMatrix(struct matrix *a, struct matrix *b)
{
    /*
    A*B = C
    A:(m x n) B:(n x p) C:(m x p)
    C(i,j) = sum(k=1; n){a(i,k) * b(k,j)}
    */
    struct matrix ret = newMatrix(a->m, b->n);
    if (a->n != b->m) // Matrizen haben inkompatible Dimensionen
    {
        ret.m = 0;
        ret.n = 0;
        return ret;
    }
    for (int i = 0; i < a->m; i++)
    {
        for (int j = 0; j < b->n; j++)
        {
            for (int k = 0; k < a->n; k++)
            {
                ret.mat[i][j] += a->mat[i][k] * b->mat[k][j];
            }
        }
    }
    return ret;
}
void printMatrix(struct matrix *mat)
{
    for (int m = 0; m < mat->m; m++)
    {
        for (int n = 0; n < mat->n; n++)
        {
            printf("%.2f\t", mat->mat[m][n]);
        }
        printf("\n\n");
    }
}


#endif