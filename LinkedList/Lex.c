#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include <string.h>



int main(int argc, char* argv[]){
    //Ensures only 3 command line args are given, Lex <input> <output>
    if (argv[3] != NULL){
        printf("stderr\n");
        exit(1);
    }

    //Make List and necessary variables
    List Sort = newList();
    char* input = strdup(argv[1]);
    char* output = strdup(argv[2]);
    FILE* read = fopen(input, "r");



    //Count the total number of line for later use
    char lineData[100];
    int index1 = 0;
    int lines = 0;
    while (fgets(lineData, sizeof(lineData), read)){
        lines++;
    }
    fclose(read);

    //Take the lines in the file and put them into an array
    FILE* read1 = fopen(input, "r");
    char** Data = malloc(sizeof(lineData) * lines);
    while (fgets(lineData, sizeof(lineData), read1)){
        Data[index1] = strdup(lineData);
        index1++;
    }
    fclose(read1);

    // Algorithm For Sorting the List
    for (int i = 0; i < index1; ++i) {
        if (i == 0){
            append(Sort, i);
            moveFront(Sort);
        } else if (i == 1){
            if (strcmp(Data[0], Data[i]) == 1) {
                prepend(Sort, i);
                moveFront(Sort);
            } else {
                append(Sort, i);
            }
        }else {
            int x = 0;
            while (x < length(Sort)) {
                if (strcmp(Data[i], Data[get(Sort)]) > 0) {
                    moveNext(Sort);
                    x++;
                    continue;
                } else {
                    insertBefore(Sort, i);
                    moveFront(Sort);
                    x = 0;
                    break;
                }
            }
            if (x == length(Sort)){
                append(Sort, i);
                moveFront(Sort);
            }
        }
    }

    FILE* out = fopen(output, "w");
    int y = 0;
    moveFront(Sort);
    while (y != length(Sort)){
        if (y == 0) {
            fprintf(out, "%s\n", Data[get(Sort)]);
            moveNext(Sort);
            y++;
        } else if (y == length(Sort)-1){
            fprintf(out, "%s", Data[get(Sort)]);
            y++;
        } else{
            fprintf(out, "%s", Data[get(Sort)]);
            moveNext(Sort);
            y++;
        }
    }
    fclose(out);

    //Test to Check if Data has the correct lines
    for (int i = 0; i < index1; ++i) {
        free(Data[i]);
    }
    free(Data);
    freeList(&Sort);
    free(input);
    free(output);
    return 0;
}