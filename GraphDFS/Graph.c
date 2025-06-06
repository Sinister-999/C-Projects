/*
 * Jestin Baath
 * 2069245
 * pa3
 */

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

typedef struct GraphObj{
    List* adj;
    int* color;
    int* parent;
    int* discover;
    int* finish;
    int order;
    int size;

}GraphObj;

//Helpers
void sortInsert(List L, int v){
    if (v > back(L)) {
        append(L, v);
    } else {
        moveFront(L);
        for (int i = 0; i < length(L); ++i) {
            if (v > get(L)) {
                moveNext(L);
                continue;
            } else if (v == get(L)) {
                return;
            } else {
                insertBefore(L, v);
                return;
            }
        }
    }
}
int search(List S, int u){
    moveFront(S);
    for (int i = 0; i < length(S); ++i) {
        if (get(S) == u){
            return 1;
        } else {
            moveNext(S);
            continue;
        }
    }
    return 0;
}

void makeNull(Graph G){
    for (int i = 0; i < G->order+1; ++i) {
        freeList(&G->adj[i]);
    }
    G->size = 0;
}


Graph newGraph(int n){
    Graph G = calloc(sizeof(GraphObj), sizeof(GraphObj));
    G->adj = calloc( n + 1,(n + 1) * sizeof(List));
    G->color = calloc( n + 1,(n + 1) * sizeof(int));
    G->discover = calloc( n + 1,(n + 1) * sizeof(int));
    G->finish = calloc( n + 1,(n + 1) * sizeof(int));
    G->parent = calloc( n + 1,(n + 1) * sizeof(int));
    G->order = n;
    G->size = 0;
    for (int i = 0; i < n+1; ++i) {
        G->adj[i] = newList();
        G->color[i] = WHITE;
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
        G->parent[i] = NIL;
    }
    return G;
}

void freeGraph(Graph* pG){
    makeNull(*pG);
    free((*pG)->adj);
    free((*pG)->color);
    free((*pG)->parent);
    free((*pG)->discover);
    free((*pG)->finish);
    free(*pG);
}

/*** Access functions ***/
int getOrder(Graph G){
    return (G->order);
}

int getSize(Graph G){
    return (G->size);
}

int getParent(Graph G, int u){
    if (1 <= u && u <= getOrder(G)) {
        return (G->parent[u]);
    } else {
        return NIL;
    }
}

int getDiscover(Graph G, int u){
    if (1 <= u && u <= getOrder(G)) {
        return (G->discover[u]);
    } else {
        return UNDEF;
    }
}

int getFinish(Graph G, int u){
    if (1 <= u && u <= getOrder(G)) {
        return (G->finish[u]);
    } else {
        return UNDEF;
    }
}


/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v){
    if (u >= 1 && u <= getOrder(G) && v >= 1 && v <= getOrder(G)) {
        if (length(G->adj[u]) > 0 && length(G->adj[v]) > 0) {
            sortInsert(G->adj[u], v);
            sortInsert(G->adj[v], u);
            G->size++;

        } else if (length(G->adj[u]) > 0) {
            sortInsert(G->adj[u], v);
            append(G->adj[v], u);
            G->size++;

        } else if (length(G->adj[v]) > 0) {
            sortInsert(G->adj[v], u);
            append(G->adj[u], v);
            G->size++;
        } else {
            append(G->adj[u], v);
            append(G->adj[v], u);
            G->size++;
        }
    }
}

void addArc(Graph G, int u, int v) {
    if (u >= 1 && u <= getOrder(G) && v >= 1 && v <= getOrder(G)) {
        if (search(G->adj[u], v) != 1) {
            if (length(G->adj[u]) == 0){
                append(G->adj[u], v);
                G->size++;
            }else {
                sortInsert(G->adj[u], v);
                G->size++;
            }
        }
    }
}

void visit(Graph G, int *pTime, int v, List S, List S1){
    int time = *pTime;
    G->discover[v] = ++time;
    G->color[v] = GRAY;
    moveFront(G->adj[v]);
    while (index(G->adj[v]) >= 0){
        int adjIndex = get(G->adj[v]);
        if (G->color[adjIndex] == WHITE){
            G->parent[adjIndex] = v;
            visit(G, &time, adjIndex, S, S1);
        }
        moveNext(G->adj[v]);
    }

    G->color[v] = BLACK;
    prepend(S1, v);
    G->finish[v] = ++time;
    *pTime = time;

}

void DFS(Graph G, List S){
    if (length(S) == getOrder(G)) {
        for (int i = 1; i < getOrder(G)+1; ++i) {
            G->color[i] = WHITE;
            G->parent[i] = NIL;
        }
        int time = 0;
        moveFront(S);
        List S1 = newList();
        while (index(S) >= 0){
            int adjIndex = get(S);
            if (G->color[adjIndex] == WHITE){
                visit(G, &time, adjIndex, S, S1);
            }
            moveNext(S);

        }
        clear(S);
        moveFront(S1);
        for (int i = 0; i < length(S1); ++i) {
            append(S, get(S1));
            moveNext(S1);
        }
        freeList(&S1);
    }
}


Graph transpose(Graph G){
    Graph out = newGraph(getOrder(G));
    for (int i = 1; i < getOrder(G)+1; ++i) {
        moveFront(G->adj[i]);
        while (G->adj >= 0) {
            if (index(G->adj[i]) >= 0) {
                addArc(out, get(G->adj[i]), i);
                moveNext(G->adj[i]);
            }else{
                break;
            }
        }
    }
    return out;

}

Graph copyGraph(Graph G){
    Graph out = newGraph(getOrder(G));
    for (int i = 1; i < getOrder(G)+1; ++i) {
        moveFront(G->adj[i]);
        while (G->adj >= 0) {
            if (index(G->adj[i]) >= 0) {
                addArc(out, i, get(G->adj[i]));
                moveNext(G->adj[i]);
            }else{
                break;
            }
        }
    }
    return out;
}

void printGraph(FILE* out, Graph G){
    //Adj List
    for (int i = 1; i < getOrder(G)+1; ++i) {
        if (length(G->adj[i]) == 0){
            fprintf(out, "%d: \n", i);
            continue;
        }
        fprintf(out, "%d: ", i);
        moveFront(G->adj[i]);
        for (int j = 0; j < length(G->adj[i]); ++j) {
            if(get(G->adj[i]) == back(G->adj[i])){
                fprintf(out, "%d\n", get(G->adj[i]));
            } else {
                fprintf(out, "%d ", get(G->adj[i]));
                moveNext(G->adj[i]);
            }
        }
    }
}