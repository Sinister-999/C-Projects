#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main() {
    Graph G = newGraph(100);
    List L = newList();
    addArc(G, 64, 4);
    addEdge(G, 64, 3);
    BFS(G, 4);
    getPath(L, G, 3)
    printf("%d %d %d %d %d ", getOrder(G), getSize(G), getSource(G), getParent(G), getDist(G));
    FILE* test = fopen("out", "w");
    printGraph(test, G)
    fclose(out);
    makeNull(G);
    freeList(&L);
    freeGraph(&G);
    return 0;


}
