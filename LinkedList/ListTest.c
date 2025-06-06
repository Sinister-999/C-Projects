#include <stdio.h>
#include "List.h"

int main(void){
    List A = newList();
    append(A, 5);
    append(A, 6);
    append(A, 4);
    append(A, 33);
    append(A, 2);
    append(A, 1);
    prepend(A, 2);

    moveFront(A);
    set(A, 9);
    printf("%d\n", length(A));
    printf("%d\n", front(A));
    printf("%d\n", front(A));
    printf("%d\n", back(A));
    printf("%d\n", get(A));
    printf("%d\n", front(A));
    List B = newList();
    printf("%d\n", equals(A, B));
    moveFront(A);
    insertAfter(A, 1);
    moveNext(A);
    moveBack(A);
    insertBefore(A, 2);
    movePrev(A);
    moveFront(A);
    deleteFront(A);
    moveBack(A);
    deleteBack(A);
    moveFront(A);
    moveNext(A);
    delete(A);
    freeList(&B);

    FILE* out = fopen("out1", "w");
    printList(out, A);
    fclose(out);
    clear(A);
    freeList(&A);
    return 0;
}