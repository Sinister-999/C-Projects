/*
 * Jestin Baath
 * 2069245
 * pa4
 */
#include <stdio.h>
#include "Matrix.h"
#include <stdlib.h>

int main(void){
    Matrix A = newMatrix(10);
    Matrix B = newMatrix(10);
    changeEntry(A, 1, 3, 0);
    changeEntry(A, 3, 3, 0);

    changeEntry(B, 1, 1, -4);
    changeEntry(A, 1, 1, 4);

    changeEntry(B, 1, 2, 0);
    changeEntry(A, 1, 2, 2);

    changeEntry(B, 2, 1, 0);
    changeEntry(A, 2, 1, 2);

    changeEntry(B, 2, 2, -2);
    changeEntry(A, 2, 2, 2);

    changeEntry(B, 2, 4, 2);

    changeEntry(A, 3, 1, 0);
    changeEntry(B, 3, 1, 0);


    changeEntry(B, 3, 2, 2);
    changeEntry(B, 7, 8, 5);
    Matrix C = sum(A, B);
    printf("%d\n", NNZ(A));
    printf("%d\n", NNZ(B));
    printf("%d\n", NNZ(C));
    Matrix D = newMatrix(3);
    for (int i = 1; i <= size(D); ++i) {
        changeEntry(D, i, 1, 1);
        changeEntry(D, i, 2, 2);
        changeEntry(D, i, 3, 3);
    }
    printMatrix(stdout, D);
    freeMatrix(&D);
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    system("leaks MatrixTest");
    return 0;
}