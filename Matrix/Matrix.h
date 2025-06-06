#ifndef MATRIX_H
#define MATRIX_H
#include<stdbool.h>


typedef double EntryElement;
typedef struct MatrixObj* Matrix;
typedef struct EntryObj* Entry;

Matrix newMatrix(int n);
void freeMatrix(Matrix* pM);
int size(Matrix M);
int NNZ(Matrix M);
int equals(Matrix M1, Matrix M2);

void makeZero(Matrix M);
void changeEntry(Matrix M, int i, int j, double x);
Matrix copy(Matrix A);
Matrix transpose(Matrix A);
Matrix scalarMult(double x, Matrix A);
Matrix sum(Matrix A, Matrix B);
Matrix diff(Matrix A, Matrix B);
Matrix product(Matrix A, Matrix B);
void printMatrix(FILE* out, Matrix M);
#endif //MATRIX_H
