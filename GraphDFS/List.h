/*
 * Jestin Baath
 * 2069245
 * pa3
 */
#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_
#include<stdbool.h>

#define FORMAT "%d"

typedef int ListElement;
typedef struct ListObj* List;
typedef struct NodeObj* Node;

void printList1(List L);
// Constructors-Destructors
List newList(void);
Node newNode(int data);
void freeList(List *pL);

// Access Functions
int length(List L);
int index(List L);
int front(List L);
int back(List L);
int get(List L);
bool equals(List A, List B);


// Manipulation procedures
void clear(List L);
void set(List L, int x);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, int x);
void append(List L, int x);
void insertBefore(List L, int x);
void insertAfter(List L, int x);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

//Other operations
void printList(FILE* out, List L);
List copyList(List L);

#endif