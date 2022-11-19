#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct // (m,n) Matrix mit n Spalten und m Zeilen
{
    float **mat;
    int m; // Zeilen
    int n; // Spalten
} matrix_t;
matrix_t newMatrix(int m, int n);
matrix_t multiplyMatrix(matrix_t a, matrix_t b);
matrix_t rotationMatrix2(float phi);
matrix_t rotationMatrix3(float phi_x_roll, float phi_y_pitch, float phi_z_yaw);
matrix_t transposeMatirx(matrix_t mat);
matrix_t einheitsMatrix(int n);
matrix_t copy_Matrix(matrix_t matrix);
void printMatrix(matrix_t mat);
bool is_equal_Matrix(matrix_t a, matrix_t b);

#endif