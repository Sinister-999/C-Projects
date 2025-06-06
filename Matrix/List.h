#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_
#include<stdbool.h>

#define FORMAT "%d"

typedef void* ListElement;
typedef struct ListObj* List;
typedef struct NodeObj* Node;

void printList1(List L);
// Constructors-Destructors
List newList(void);
Node newNode(void* data);
void freeList(List *pL);

// Access Functions
int length(List L);
int index(List L);
void* front(List L);
void* back(List L);
void* get(List L);


// Manipulation procedures
void clear(List L);
void set(List L, void* x);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, void* x);
void append(List L, void* x);
void insertBefore(List L, void* x);
void insertAfter(List L, void* x);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

//Other operations
void printList(FILE* out, List L);
#endif
