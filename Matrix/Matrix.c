/*
 * Jestin Baath
 * 2069245
 * pa4
 */
#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include "List.h"


typedef struct EntryObj{
    int column;
    EntryElement data;
}EntryObj;

typedef struct MatrixObj{
    int size;
    int NNZ;
    List* data;
}MatrixObj;

/*** Helper ***/
double vectorDot(List F, List Q){
    double sum = 0;
    if (length(F) == 0 || length(Q) == 0){
        return sum;
    } else{
        moveFront(F);
        moveFront(Q);
        while (index(F) >= 0 || index(Q) >= 0){
            if (index(F) < 0){
                moveNext(Q);
            } else if (index(Q) < 0){
                moveNext(F);
            } else {
                Entry x = get(F);
                Entry y = get(Q);
                if (x->column > y->column) {
                    moveNext(Q);
                } else if (y->column > x->column) {
                    moveNext(F);
                } else {
                    sum = sum + (x->data * y->data);
                    moveNext(Q);
                    moveNext(F);
                }
            }
        }
        return sum;
    }

}

/*** Constructors and Deconstructors ***/
Matrix newMatrix(int n){
    Matrix out = calloc(sizeof(MatrixObj), sizeof(MatrixObj));
    out->size = n;
    out->NNZ = 0;
    out->data = calloc(n+1,sizeof(List) * n+1);
    for(int i = 0; i < n+1; i++){
        out->data[i] = newList();
    }
    return out;
}

void freeMatrix(Matrix* pM){
    makeZero(*pM);
    for (int i = 0; i <= size(*pM); ++i) {
        freeList(&((*pM)->data[i]));
    }
    free((*pM)->data);
    free(*pM);
}

/*** Access Functions ***/
int size(Matrix M){
    return M->size;
}

int NNZ(Matrix M){
    return M->NNZ;
}

int equals(Matrix M1, Matrix M2){
    if(M1 == M2){
        return 1;
    }
    if (size(M1) != size(M2)){
        return 0;
    }
    if (NNZ(M1) != NNZ(M2)){
        return 0;
    }
    for (int i = 1; i <= M1->size; ++i) {
        if (length(M1->data[i]) != length(M2->data[i])){
            return 0;
        } else {
            if (length(M1->data[i]) == 0){
                continue;
            }
            moveFront(M1->data[i]);
            moveFront(M2->data[i]);
            while (index(M1->data[i]) >= 0) {
                Entry x = get(M1->data[i]);
                Entry y = get(M2->data[i]);
                if (x->column != y->column) {
                    return 0;
                }else if (x->data != y->data) {
                    return 0;
                }
                moveNext(M1->data[i]);
                moveNext(M2->data[i]);
            }
        }
    }
    return 1;
}

/** Manipulation Procedures **/
void makeZero(Matrix M){
    for (int i = 1; i <= M->size; ++i) {
        if (length(M->data[i]) == 0){
            continue;
        } else{
            moveFront(M->data[i]);
            while (index(M->data[i]) >= 0){
                Entry x = get(M->data[i]);
                free(x);
                moveNext(M->data[i]);
            }
        }
        clear(M->data[i]);
    }
    M->NNZ = 0;
}

void changeEntry(Matrix M, int i, int j, double x){
    if (1 <= i && i <= M->size && j <= M->size && j >= 1){
        if (x == 0) {
            if (length(M->data[i]) == 0) {
                return;
            } else{
                moveFront(M->data[i]);
                while (index(M->data[i]) >= 0){
                    Entry e = get(M->data[i]);
                    if (j == e->column){
                        delete(M->data[i]);
                        free(e);
                        M->NNZ--;
                        return;
                    } else{
                        moveNext(M->data[i]);
                    }
                }
            }
        } else {
            if (length(M->data[i]) == 0){
                Entry e = calloc(sizeof(EntryObj),sizeof(EntryObj));
                e->data = x; e->column = j;
                append(M->data[i], e);
                M->NNZ++;
            } else{
                moveFront(M->data[i]);
                while (index(M->data[i]) >= 0){
                    Entry check = get(M->data[i]);
                    if (j == check->column){
                        Entry e = calloc(sizeof(EntryObj),sizeof(EntryObj));
                        e->data = x; e->column = j;
                        free(check);
                        set(M->data[i], e);
                        return;
                    } else if(j > check->column){
                        moveNext(M->data[i]);
                    } else if (check->column > j){
                        Entry e = calloc(sizeof(EntryObj),sizeof(EntryObj));
                        e->data = x; e->column = j;
                        insertBefore(M->data[i], e);
                        M->NNZ++;
                        return;
                    }
                }
                Entry e = calloc(sizeof(EntryObj),sizeof(EntryObj));
                e->data = x; e->column = j;
                append(M->data[i], e);
                M->NNZ++;
            }
        }
    }
}


/** Arithmetic Operations **/
Matrix copy(Matrix A){
    Matrix out = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        if (length(A->data[i]) == 0){
            continue;
        } else {
            moveFront(A->data[i]);
            while (index(A->data[i]) >= 0) {
                Entry x = get(A->data[i]);
                changeEntry(out, i, x->column, x->data);
                moveNext(A->data[i]);
            }
        }
    }
    return out;
}

Matrix transpose(Matrix A){
    Matrix out = newMatrix(A->size);
    for (int i = 0; i <= A->size; ++i) {
        if (length(A->data[i]) == 0){
            continue;
        } else {
            moveFront(A->data[i]);
            while (index(A->data[i]) >= 0){
                Entry x = get(A->data[i]);
                changeEntry(out, x->column, i, x->data);
                moveNext(A->data[i]);
            }
        }
    }
    return out;
}

Matrix scalarMult(double x, Matrix A){
    Matrix out = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        if (length(A->data[i]) == 0){
            continue;
        } else {
            moveFront(A->data[i]);
            while (index(A->data[i]) >= 0) {
                Entry y = get(A->data[i]);
                changeEntry(out, i, y->column, (y->data) * x);
                moveNext(A->data[i]);
            }
        }
    }
    return out;
}

Matrix sum(Matrix A, Matrix B){
    if (size(A) == size(B)){
        if (A == B){
            Matrix out1 = scalarMult(2, A);
            return out1;
        } else {
            Matrix out = newMatrix(A->size);
            for (int i = 1; i <= A->size; ++i) {
                if (length(A->data[i]) == 0 && length(B->data[i]) == 0) {
                    continue;
                } else if (length(A->data[i]) == 0) {
                    moveFront(B->data[i]);
                    while (index(B->data[i]) >= 0) {
                        Entry x = get(B->data[i]);
                        changeEntry(out, i, x->column, x->data);
                        moveNext(B->data[i]);
                    }
                } else if (length(B->data[i]) == 0) {
                    moveFront(A->data[i]);
                    while (index(A->data[i]) >= 0) {
                        Entry x = get(A->data[i]);
                        changeEntry(out, i, x->column, x->data);
                        moveNext(A->data[i]);
                    }
                } else {
                    moveFront(A->data[i]);
                    moveFront(B->data[i]);
                    while (index(A->data[i]) >= 0|| index(B->data[i]) >= 0) {
                        if(index(A->data[i]) < 0){
                            Entry y = get(B->data[i]);
                            changeEntry(out, i, y->column, y->data);
                            moveNext(B->data[i]);
                        } else if (index(B->data[i]) < 0){
                            Entry x = get(A->data[i]);
                            changeEntry(out, i, x->column, x->data);
                            moveNext(A->data[i]);
                        }else {
                            Entry x = get(A->data[i]);
                            Entry y = get(B->data[i]);
                            if (x->column == y->column) {
                                changeEntry(out, i, x->column, (x->data + y->data));
                                moveNext(A->data[i]);
                                moveNext(B->data[i]);
                            } else if (x->column > y->column) {
                                changeEntry(out, i, y->column, y->data);
                                moveNext(B->data[i]);
                            } else if (y->column > x->column) {
                                changeEntry(out, i,x->column,  x->data);
                                moveNext(A->data[i]);
                            }
                        }
                    }
                }
            }
            return out;
        }

    }
    printf("Size of Matrix A Does not equal size of Matrix B");
    exit(1);
}

Matrix diff(Matrix A, Matrix B){
    if (size(A) == size(B)){
        Matrix out = newMatrix(A->size);
        if (A == B){
            return out;
        } else {
            for (int i = 1; i <= A->size; ++i) {
                if (length(A->data[i]) == 0 && length(B->data[i]) == 0) {
                    continue;
                } else if (length(A->data[i]) == 0) {
                    moveFront(B->data[i]);
                    while (index(B->data[i]) >= 0) {
                        Entry x = get(B->data[i]);
                        changeEntry(out, i, x->column, (x->data) * -1);
                        moveNext(B->data[i]);
                    }
                } else if (length(B->data[i]) == 0) {
                    moveFront(A->data[i]);
                    while (index(A->data[i]) >= 0) {
                        Entry x = get(A->data[i]);
                        changeEntry(out, i, x->column, x->data);
                        moveNext(A->data[i]);
                    }
                } else {
                    moveFront(A->data[i]);
                    moveFront(B->data[i]);
                    while (index(A->data[i]) >= 0|| index(B->data[i]) >= 0) {
                        if(index(A->data[i]) < 0){
                            Entry y = get(B->data[i]);
                            changeEntry(out, i, y->column, (y->data) * -1);
                            moveNext(B->data[i]);
                        } else if (index(B->data[i]) < 0){
                            Entry x = get(A->data[i]);
                            changeEntry(out, i, x->column, x->data);
                            moveNext(A->data[i]);
                        }else {
                            Entry x = get(A->data[i]);
                            Entry y = get(B->data[i]);
                            if (x->column == y->column) {
                                changeEntry(out, i, x->column, (x->data - y->data));
                                moveNext(A->data[i]);
                                moveNext(B->data[i]);
                            } else if (x->column > y->column) {
                                changeEntry(out, i, y->column, (y->data) * -1);
                                moveNext(B->data[i]);
                            } else if (y->column > x->column) {
                                changeEntry(out, i,x->column,  x->data);
                                moveNext(A->data[i]);
                            }
                        }
                    }
                }
            }
            return out;
        }
    }
    printf("Size of Matrix A Does not equal size of Matrix B");
    exit(1);
}

Matrix product(Matrix A, Matrix B){
    if (size(A) == size(B)) {
        Matrix out = newMatrix(A->size);
        if (A == B){
            Matrix temp = transpose(A);
            for (int i = 1; i <= A->size; ++i) {
                for (int j = 1; j <= A->size; ++j) {
                    changeEntry(out, i, j, vectorDot(A->data[i], temp->data[j]));
                }
            }
            freeMatrix(&temp);
        } else{
            Matrix temp = transpose(B);
            for (int i = 1; i <= A->size; ++i) {
                for (int j = 1; j <= A->size; ++j) {
                    changeEntry(out, i, j, vectorDot(A->data[i], temp->data[j]));
                }
            }
            freeMatrix(&temp);
        }
        return out;
    } else{
        printf("Size of Matrix A Does not equal size of Matrix B");
        exit(1);
    }
}

void printMatrix(FILE* out, Matrix M){
    for (int i = 1; i <= M->size; ++i) {
        if (length(M->data[i]) != 0) {
            fprintf(out, "%d: ", i);
            moveFront(M->data[i]);
            while (index(M->data[i]) >= 0) {
                Entry e = get(M->data[i]);
                fprintf(out, "(%d, %.1f) ", e->column, e->data);
                moveNext(M->data[i]);
            }
            fprintf(out, "\n");
        }
    }
    fprintf(out, "\n");
}