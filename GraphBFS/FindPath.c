#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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
    char* check1 = "0 0\n";
    char* check2 = "0 0";
    bool check_1 = false;
    int i = 0;
    int size;
    while (fgets(lineData, sizeof(lineData), read)){
        if(strcmp(lineData, check2) == 0){
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
    int* Data1 = malloc(sizeof(lineData) * lines);
    int* Data2 = malloc(sizeof(lineData) * lines);
    int* DataDis1 = malloc(sizeof(lineData) * lines);
    int* DataDis2 = malloc(sizeof(lineData) * lines);
    int index1 = 0;
    int index2 = 0;
    i = 0;
    while (fgets(lineData, sizeof(lineData), read)){
        if (i==0){
            i++;
            continue;
        } else if (check_1 == false){
            if (strcmp(lineData, check1) == 0){
                check_1 = true;
            } else {
                char *temp = strtok(lineData, " \n");
                Data1[index1] = atoi(temp);
                temp = strtok(NULL, " \n");
                Data2[index1] = atoi(temp);
                index1++;
            }
        } else {
            if(strcmp(lineData, check2) == 0||strcmp(lineData, check1) == 0){
                break;
            } else {
                char *temp = strtok(lineData, " \n");
                DataDis1[index2] = atoi(temp);
                temp = strtok(NULL, " \n");
                DataDis2[index2] = atoi(temp);
                index2++;
            }
        }


    }
    fclose(read1);
    Graph G = newGraph(size+1);
    for (int i = 0; i < index1; ++i) {
        addEdge(G, Data1[i], Data2[i]);
    }
    FILE* out = fopen(output, "w");
    printGraph(out, G);

    for (int j = 0; j < index2; ++j) {
        fprintf(out, "\n");
        BFS(G, DataDis1[j]);
        List L = newList();
        int dist = getDist(G, DataDis2[j]);
        getPath(L, G, DataDis2[j]);
        if (dist == -1){
            fprintf(out, "The distance from %d to %d is infinity\n", DataDis1[j], DataDis2[j]);
            fprintf(out, "No %d-%d path exists\n", DataDis1[j], DataDis2[j]);
        } else {
            fprintf(out, "The distance from %d to %d is %d\n", DataDis1[j], DataDis2[j], dist);
            fprintf(out, "A shortest %d-%d path is: ", DataDis1[j], DataDis2[j]);
            moveFront(L);
            for (int k = 0; k < length(L); ++k) {
                if (get(L) == back(L)) {
                    fprintf(out, "%d\n", get(L));
                } else {
                    fprintf(out, "%d ", get(L));
                    moveNext(L);
                }
            }

        }
        freeList(&L);
    }
    fclose(out);
    free(Data1);
    free(Data2);
    free(DataDis1);
    free(DataDis2);
    freeGraph(&G);
    return 0;
}
