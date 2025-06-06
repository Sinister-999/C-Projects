/*
 * Jestin Baath
 * 2069245
 * PA2
 * Graph.c - Makes a Graph ADT and functions for it
 */

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"


typedef struct GraphObj{
    List* adj;
    int* color;
    int* parent;
    int* dist;
    int order;
    int size;
    int source;
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

/*** Constructors-Destructors ***/
Graph newGraph(int n){
    Graph G = calloc(sizeof(GraphObj), sizeof(GraphObj));
    G->adj = calloc( n + 1,(n + 1) * sizeof(List));
    G->color = calloc( n + 1,(n + 1) * sizeof(int));
    G->dist = calloc( n + 1,(n + 1) * sizeof(int));
    G->parent = calloc( n + 1,(n + 1) * sizeof(int));
    G->order = n;
    G->size = 0;
    G->source = NIL;
    for (int i = 0; i < n+1; ++i) {
        G->adj[i] = newList();
        G->color[i] = WHITE;
        G->dist[i] = INF;
        G->parent[i] = NIL;
    }
    return G;
}

void freeGraph(Graph* pG){
    makeNull(*pG);
    free((*pG)->adj);
    free((*pG)->color);
    free((*pG)->dist);
    free((*pG)->parent);
    free(*pG);
}

/*** Access functions ***/
int getOrder(Graph G){
    return (G->order);
}

int getSize(Graph G){
    return (G->size);
}

int getSource(Graph G){
    return (G->source);
}

int getParent(Graph G, int u){
    if (u >= 1 && u <= getOrder(G)) {
        return (G->parent[u]);
    } else {
        return NIL;
    }
}

int getDist(Graph G, int u){
    if (u >= 1 && u <= getOrder(G)) {
        return (G->dist[u]);
    } else {
        return INF;
    }
}

void getPath(List L, Graph G, int u){
    if (u >= 1 && u <= getOrder(G) && getSource(G) != NIL) {
        if (G->dist[u] == INF){
            append(L, NIL);
        } else {
            int temp = u;
            temp = G->parent[temp];
            while (temp != NIL){
                prepend(L, temp);
                temp = G->parent[temp];
            }
            append(L, u);
        }
    }
}

/*** Manipulation procedures ***/
void makeNull(Graph G){
   for (int i = 0; i < G->order+1; ++i) {
       freeList(&G->adj[i]);
   }
   G->size = 0;
}

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

void addArc(Graph G, int u, int v){
    if (u >= 1 && u <= getOrder(G) && v >= 1 && v <= getOrder(G)) {
        if (length(G->adj[u]) > 0) {
            sortInsert(G->adj[u], v);
            G->size++;
        } else {
            append(G->adj[u],v);
            G->size++;
        }
    }
}

void BFS(Graph G, int s){
    if (s >= 1 && s <= getOrder(G)) {
        for (int i = 0; i < getOrder(G); ++i) {
            G->color[i] = WHITE;
            G->dist[i] = INF;
            G->parent[i] = NIL;
        }

        G->source = s;
        G->color[s] = GRAY;
        G->dist[s] = 0;
        G->parent[s] = NIL;

        List temp = newList();
        append(temp, s);
        while (length(temp) > 0) {
            int x = front(temp);
            deleteFront(temp);
            moveFront(G->adj[x]);
            for (int i = 0; i < length(G->adj[x]); ++i) {
                int y = get(G->adj[x]);
                if (G->color[y] == WHITE) {
                    G->color[y] = GRAY;
                    G->dist[y] = G->dist[x] + 1;
                    G->parent[y] = x;
                    append(temp, y);
                }
                moveNext(G->adj[x]);
            }
            G->color[x] = BLACK;
        }
        freeList(&temp);
    }
}

/*** Other operations ***/
void printGraph(FILE* out, Graph G){
    //Adj List
    for (int i = 1; i < getOrder(G); ++i) {
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
