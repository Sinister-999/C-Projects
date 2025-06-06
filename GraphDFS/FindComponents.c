/*
 * Jestin Baath
 * 2069245
 * pa3
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#include "Graph.h"


int main(int argc, char* argv[]){
    if (argv[3] != NULL){
        printf("stderr\n");
        exit(1);
    }
    
    char* input = strdup(argv[1]);
    char* output = strdup(argv[2]);
    FILE* read = fopen(input, "r");


    //Count the total number of line for later use
    char lineData[100];
    int lines = 0;
    char* check1 = "0 0";
    int i = 0;
    int size;
    while (fgets(lineData, sizeof(lineData), read)){
        if(strcmp(lineData, check1) == 0){
            break;
        } else if(i == 0){
            char* temp = strtok(lineData, " \n");
            size = atoi(temp);
            i++;
        }
        lines++;
    }
    fclose(read);

    FILE* read1 = fopen(input, "r");
    int* Data1 = calloc(lines,sizeof(lineData) * lines);
    int* Data2 = calloc(lines,sizeof(lineData) * lines);
    int inde = 0;
    i = 0;
    int temp5;
    fscanf(read1, "%d", &temp5);
    for (int j = 0; j < lines; ++j) {
        fscanf(read1, "%d %d", &Data1[inde], &Data2[inde]);
        inde++;
    }


    Graph G = newGraph(size);
    for (int j = 0; j < inde+1; ++j) {
        addArc(G, Data1[j], Data2[j]);
    }
    FILE* out = fopen(output, "w");
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");
    List L = newList();
    for (int j = 1; j <= size; ++j) {
        append(L, j);
    }
    Graph Gt = transpose(G);
    DFS(G, L);
    DFS(Gt, L);
    moveFront(L);
    int in = 0;
    moveFront(L);
    while (index(L) >= 0) {
        if (getParent(Gt, get(L)) == NIL) {
            in++;
        }
        moveNext(L);
    }

    fprintf(out, "G contains %d strongly connected components:\n", in);
    moveFront(L);
    while (getParent(Gt, get(L)) != NIL){
        moveNext(L);
        if (index(L) == -1){
            break;
        }
    }

    moveBack(L);
    for (int j = 1; j < in+1; ++j) {
        fprintf(out, "Component %d: ", j);
        List temp = newList();
        while (getParent(Gt, get(L)) != 0){
            prepend(temp, get(L));
            movePrev(L);
        }
        prepend(temp, get(L));
        movePrev(L);
        printList(out, temp);
        fprintf(out, "\n");
        freeList(&temp);
    }
    fclose(read1);
    fclose(out);
    free(input);
    free(output);
    free(Data1);
    free(Data2);
    freeList(&L);
    freeGraph(&G);
    freeGraph(&Gt);
    return 0;
}