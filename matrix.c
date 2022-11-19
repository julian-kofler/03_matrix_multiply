#ifndef MATRIX_C
#define MATRIX_C

#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

matrix_t newMatrix(int m, int n)
{
    matrix_t ret = {
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
matrix_t multiplyMatrix(matrix_t a, matrix_t b)
{
    /*
    A*B = C
    A:(m x n) B:(n x p) C:(m x p)
    C(i,j) = sum(k=1; n){a(i,k) * b(k,j)}
    */
    matrix_t ret = newMatrix(a.m, b.n);
    if (a.n != b.m) // Matrizen haben inkompatible Dimensionen
    {
        ret.m = 0;
        ret.n = 0;
        return ret;
    }
    for (int i = 0; i < a.m; i++)
    {
        for (int j = 0; j < b.n; j++)
        {
            for (int k = 0; k < a.n; k++)
            {
                ret.mat[i][j] += a.mat[i][k] * b.mat[k][j];
            }
        }
    }
    return ret;
}
matrix_t rotationMatrix2(float phi)
{
    matrix_t rot2 = newMatrix(2, 2);
    rot2.mat[0][0] = cos(phi);
    rot2.mat[0][1] = -sin(phi);
    rot2.mat[1][0] = sin(phi);
    rot2.mat[1][1] = cos(phi);
}
matrix_t rotationMatrix3(float phi_x_roll, float phi_y_pitch, float phi_z_yaw)
{
    matrix_t
        x_roll = newMatrix(3, 3),
        y_pitch = newMatrix(3, 3),
        z_yaw = newMatrix(3, 3);

    x_roll.mat[0][0] = 1;
    x_roll.mat[0][1] = 0;
    x_roll.mat[0][2] = 0;
    x_roll.mat[1][0] = 0;
    x_roll.mat[1][1] = cos(phi_x_roll);
    x_roll.mat[1][2] = -sin(phi_x_roll);
    x_roll.mat[2][0] = 0;
    x_roll.mat[2][1] = sin(phi_x_roll);
    x_roll.mat[2][2] = cos(phi_x_roll);

    y_pitch.mat[0][0] = cos(phi_y_pitch);
    y_pitch.mat[0][1] = 0;
    y_pitch.mat[0][2] = sin(phi_y_pitch);
    y_pitch.mat[1][0] = 0;
    y_pitch.mat[1][1] = 1;
    y_pitch.mat[1][2] = 0;
    y_pitch.mat[2][0] = -sin(phi_y_pitch);
    y_pitch.mat[2][1] = 0;
    y_pitch.mat[2][2] = cos(phi_y_pitch);

    z_yaw.mat[0][0] = cos(phi_z_yaw);
    z_yaw.mat[0][1] = -sin(phi_z_yaw);
    z_yaw.mat[0][2] = 0;
    z_yaw.mat[1][0] = sin(phi_z_yaw);
    z_yaw.mat[1][1] = cos(phi_z_yaw);
    z_yaw.mat[1][2] = 0;
    z_yaw.mat[2][0] = 0;
    z_yaw.mat[2][1] = 0;
    z_yaw.mat[2][2] = 1;

    matrix_t rot = {0};
    rot = multiplyMatrix(x_roll, y_pitch);
    rot = multiplyMatrix(rot, z_yaw);
    return rot;
}
matrix_t transposeMatirx(matrix_t mat)
{
    matrix_t ret = newMatrix(mat.n, mat.m);
    for (int m = 0; m < ret.m; m++)
    {
        for (int n = 0; n < ret.n; n++)
        {
            ret.mat[m][n] = mat.mat[n][m];
        }
    }
    return ret;
}
matrix_t einheitsMatrix(int n)
{
    matrix_t ret = newMatrix(n, n);
    for (int i = 0; i < n; i++)
    {
        ret.mat[i][i] = 1;
    }
    return ret;
}
matrix_t copy_Matrix(matrix_t matrix)
{
    matrix_t ret = newMatrix(matrix.m, matrix.n);
    for (int m = 0; m < ret.m; m++)
    {
        for (int n = 0; n < ret.n; n++)
        {
            ret.mat[m][n] = matrix.mat[m][n];
        }
    }
    return ret;
}
void printMatrix(matrix_t mat)
{
    for (int m = 0; m < mat.m; m++)
    {
        for (int n = 0; n < mat.n; n++)
        {
            printf("%.2f\t", mat.mat[m][n]);
        }
        printf("\n\n");
    }
}
bool is_equal_Matrix(matrix_t a, matrix_t b)
{
    if (a.m != b.m || a.n != b.n)
    {
        return false;
    }
    for (int n = 0; n < a.n; n++)
    {
        for (int m = 0; m < b.m; m++)
        {
            if (a.mat[n][m] != b.mat[n][m])
            {
                return false;
            }
        }
    }
    return true;
}
void free_Matrix(matrix_t x)
{
    for (int i = 0; i < x.m; i++)
    {
        free(x.mat[i]);
    }
    free(x.mat);
}

#endif