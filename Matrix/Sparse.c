/*
 * Jestin Baath
 * 2069245
 * pa4
 */
#include <stdio.h>
#include "Matrix.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){
    if (argv[3] != NULL){
        printf("stderr\n");
        exit(1);
    }

    char* input = strdup(argv[1]);
    char* output = strdup(argv[2]);
    FILE* read = fopen(input, "r");
    FILE* out = fopen(output, "w");

    int temp[3];
    int size;
    fscanf(read, "%d %d %d", &size, &temp[1], &temp[2]);
    int aRow[temp[1]]; int aCol[temp[1]]; double aValue[temp[1]]; int aCount = 0;
    int Row; int Col; double Val;
    int bRow[temp[2]]; int bCol[temp[2]]; double bValue[temp[1]]; int bCount = 0;
    while (fscanf(read, "%d %d %lf", &Row, &Col, &Val) != EOF){
        if(aCount < temp[1]){
            aRow[aCount] = Row; aCol[aCount] = Col; aValue[aCount] = Val;
            aCount++;
        } else if(bCount < temp[2]){
            bRow[bCount] = Row; bCol[bCount] = Col; bValue[bCount] = Val;
            bCount++;
        } else {continue;}
    }

    Matrix A = newMatrix(size);
    for (int i = 0; i < temp[1]; ++i) {
        changeEntry(A, aRow[i], aCol[i], aValue[i]);
    }
    Matrix B = newMatrix(size);
    for (int i = 0; i < temp[2]; ++i) {
        changeEntry(B, bRow[i], bCol[i], bValue[i]);
    }

    fprintf(out, "A has %d non-zero entries:\n", temp[1]);
    printMatrix(out, A);

    fprintf(out, "B has %d non-zero entries:\n", temp[2]);
    printMatrix(out, B);

    fprintf(out, "(1.5)*A =\n");
    Matrix A1 = scalarMult(1.5, A);
    printMatrix(out, A1);
    freeMatrix(&A1);

    fprintf(out, "A+B =\n");
    A1 = sum(A, B);
    printMatrix(out, A1);
    freeMatrix(&A1);

    fprintf(out, "A+A =\n");
    A1 = sum(A, A);
    printMatrix(out, A1);
    freeMatrix(&A1);

    fprintf(out, "B-A =\n");
    A1 = diff(B, A);
    printMatrix(out, A1);
    freeMatrix(&A1);

    fprintf(out, "A-A =\n");
    A1 = diff(A, A);
    printMatrix(out, A1);
    freeMatrix(&A1);

    fprintf(out, "Transpose (A) =\n");
    A1 = transpose(A);
    printMatrix(out, A1);
    freeMatrix(&A1);

    fprintf(out, "A*B =\n");
    A1 = product(A, B);
    printMatrix(out, A1);
    freeMatrix(&A1);

    fprintf(out, "B*B =\n");
    A1 = product(B, B);
    printMatrix(out, A1);
    freeMatrix(&A1);

    fclose(out);
    fclose(read);
    free(input);
    free(output);
    freeMatrix(&A);
    freeMatrix(&B);
    return 0;
}
