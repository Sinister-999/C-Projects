/*
 * Jestin Baath
 * 2069245
 * pa3
 */
#include <stdio.h>
#include "List.h"
#include "Graph.h"

int main(void){
    Graph A = newGraph(5);
    List L = newList();

    addArc(A, 1, 4);
    addArc(A, 1, 3);
    addArc(A, 1, 2);
    Graph B = transpose(A);
    Graph C = copyGraph(A);
    
    printGraph(stdout, A);
    printGraph(stdout, C);
    printGraph(stdout, B);

}