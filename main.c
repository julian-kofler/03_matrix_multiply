#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "matrix.c"

void test_multiply(matrix_t a, matrix_t b)
{
    matrix_t
        res_ber = newMatrix(3, 1),
        res_real = newMatrix(3, 1);
    
    res_real.mat[0][0] = 10;
    res_real.mat[1][0] = 22;
    res_real.mat[2][0] = 14;

    res_ber = multiplyMatrix(a, b);

    printf("a:\n"); printMatrix(a);
    printf("b:\n"); printMatrix(b);
    printf("res_ber:\n"); printMatrix(res_ber);
    printf("res_real:\n"); printMatrix(res_real);
    printf("test: %s\n", is_equal_Matrix(res_ber, res_real) ? "bestanden" : "failed");
}
void test_rotate(void)
{
    matrix_t x = einheitsMatrix(3);
    matrix_t rotator = rotationMatrix2(90);
    matrix_t rotated = multiplyMatrix(x, rotator);
    printf("gedrehte Matrix: \n");
    printMatrix(rotated);
}
void test(void)
{
    matrix_t
        a = newMatrix(3, 2),
        b = newMatrix(2, 1);

    a.mat[0][0] = 1;
    a.mat[0][1] = 2;
    a.mat[1][0] = 3;
    a.mat[1][1] = 4;
    a.mat[2][0] = 5;
    a.mat[2][1] = 1;

    b.mat[0][0] = 2;
    b.mat[1][0] = 4;

    test_multiply(a, b);
    test_rotate();
}
int main(int argc, char const *argv[])
{
    test();
    return 0;
}
