/*
 * Jestin Baath
 * 2069245
 * pa3
 */

#ifndef PA3_GRAPH_H
#define PA3_GRAPH_H

#define UNDEF -1
#define NIL 0
#define WHITE 0
#define GRAY  1
#define BLACK 2

#include "List.h"

typedef struct GraphObj* Graph;

void sortInsert(List L, int v);
/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);

/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);

/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);

#endif //PA3_GRAPH_H
