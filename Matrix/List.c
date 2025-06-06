#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "List.h"

//private Strct Def--------------------------------------------------

typedef struct NodeObj {
    ListElement data;
    Node next;
    Node prev;
}NodeObj;

typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int length;
    int cursorPos; //Index for Cursor
}ListObj;

// Constructors-Destructors-----------------------------------------
// Create A list
List newList(void){
    List L = calloc(sizeof(List), sizeof(List));
    assert(L != NULL);
    L->length = 0;
    L->cursorPos = -1;
    L->front = L->back = L->cursor = NULL;
    return(L);
}

// Frees a List
void freeList(List *pL){
    if (*pL != NULL && pL != NULL){
        clear(*pL);
    }
    free(*pL);
}

// Creates a new node
Node newNode(void* data){
    Node node = malloc(sizeof(NodeObj));
    assert(node != NULL);
    node->data = data;
    node->next = node->prev = NULL;
    return(node);
}

// Access functions--------------------------------------------------
int length(List L){
    return(L->length);
}

int index(List L){
    return(L->cursorPos);
}

void* front(List L){
    if (L->length > 0){
        return(L->front->data);
    }else{
        printf("List Error: calling front() on an empty List\n");
        exit(EXIT_FAILURE);
    }
}

void* back(List L){
    if (L->length > 0){
        return(L->back->data);
    }else{
        printf("List Error: calling back() on an empty List\n");
        exit(EXIT_FAILURE);
    }
}

void* get(List L){
    if (L->length > 0 && L->cursorPos >= 0){
        return(L->cursor->data);
    }else if (L->length <= 0){
        printf("List Error: calling get() on an empty List\n");
        exit(EXIT_FAILURE);
    }else {
        printf("List Error: calling get() without a cursor set\n");
        exit(EXIT_FAILURE);
    }
}

// Manipulation procedures --------------------------------------------
// Clears the list
void clear(List L){
    L->cursor = NULL;
    L->cursorPos = -1;
    while (L->front != NULL){
        deleteFront(L);
    }
    L->back = NULL;
}

//
void set(List L, void* x){
    if (L->length != 0 && L->cursorPos >= 0){
        L->cursor->data = x;
    } else if (L->length == 0){
        printf("List Error: calling set() on an empty List\n");
        exit(EXIT_FAILURE);
    }else {
        printf("List Error: calling set() without a cursor set\n");
        exit(EXIT_FAILURE);
    }
}

//
void moveFront(List L){
    if (L->length != 0){
        L->cursor = L->front;
        L->cursorPos = 0;
    }
}

void moveBack(List L){
    if (L->length != 0){
        L->cursor = L->back;
        L->cursorPos = L->length - 1;
    }
}

void movePrev(List L){
    if (L->cursor != NULL){
        if (L->cursor == L->front){
            L->cursor = NULL;
            L->cursorPos = -1;
        } else{
            L->cursor = L->cursor->prev;
            L->cursorPos--;
        }
    }
}

void moveNext(List L){
    if (L->cursor != NULL){
        if (L->cursor == L->back){
            L->cursor = NULL;
            L->cursorPos = -1;
        } else{
            L->cursor = L->cursor->next;
            L->cursorPos++;
        }
    }
}

// Adds a new node to the back
void prepend(List L, void* x){
    if(index(L) != -1){
        L->cursorPos++;
    }
    if (L->length == 0){
        Node n = newNode(x);
        L->front = L->back = n;
        L->length++;
    } else{
        Node n = newNode(x);
        n->next = L->front;
        L->front->prev = n;
        L->front = n;
        L->length++;
    }
}

// Adds a new node to the front
void append(List L, void* x){
    if (L->length == 0){
        Node n = newNode(x);
        L->front = L->back = n;
        L->length++;
    }else{
        Node n = newNode(x);
        n->prev = L->back;
        L->back->next = n;
        L->back = n;
        L->length++;
    }
}

void insertBefore(List L, void* x){
    if (L->length != 0 && L->cursorPos >= 0) {
        if (index(L) == 0) {
            prepend(L, x);
        } else {
            Node n = newNode(x);
            n->prev = L->cursor->prev;
            L->cursor->prev->next = n;
            n->next = L->cursor;
            L->cursor->prev = n;
            L->length++;
            L->cursorPos++;
        }

    } else if (L->length == 0){
        printf("List Error: calling insertBefore() on an empty List\n");
        exit(EXIT_FAILURE);
    }else {
        printf("List Error: calling insertBefore() without a cursor set\n");
        exit(EXIT_FAILURE);
    }
}

void insertAfter(List L, void* x){
    if (L->length != 0 && L->cursorPos >= 0){
        if (index(L) == L->length-1) {
            append(L, x);
        } else {
            Node n = newNode(x);
            n->next = L->cursor->next;
            L->cursor->next->prev = n;
            n->prev = L->cursor;
            L->cursor->next = n;
            L->length++;
        }
    } else if (L->length == 0){
        printf("List Error: calling insertAfter() on an empty List\n");
        exit(EXIT_FAILURE);
    } else {
        printf("List Error: calling insertAfter() without a cursor set\n");
        exit(EXIT_FAILURE);
    }
}

void deleteFront(List L) {
    if (L->length == 1){
        free(L->front);
        L->front = L->back = L->cursor = NULL;
        L->cursorPos = -1;
        L->length--;
    } else if (L->length != 0){
        if (L->cursor == L->front){
            L->cursor = NULL;
            L->cursorPos = -1;
        } else if (index(L) != -1){
            L->cursorPos--;
        }
        L->front = L->front->next;
        free(L->front->prev);
        L->front->prev = NULL;
        L->length--;

    } else {
        printf("List Error: calling deleteFront() on an empty List\n");
        exit(EXIT_FAILURE);
    }
}

void deleteBack(List L){
    if (L->length == 1){
        deleteFront(L);
    } else if (L->length != 0){
        if (L->cursor == L->back){
            L->cursor = NULL;
            L->cursorPos = -1;
        }
        L->back = L->back->prev;
        free(L->back->next);
        L->back->next = NULL;
        L->length--;
    } else {
        printf("List Error: calling deleteFront() on an empty List\n");
        exit(EXIT_FAILURE);
    }
}

void delete(List L){
    if (L->length != 0 && L->cursorPos >= 0){
        if (L->cursor == L->front){
            deleteFront(L);
        } else if (L->cursor == L->back){
            deleteBack(L);
        } else {
            L->cursor->prev->next = L->cursor->next;
            L->cursor->next->prev = L->cursor->prev;
            L->cursor->next = NULL;
            L->cursor->prev = NULL;
            free(L->cursor);
            L->cursor = NULL;
            L->cursorPos = -1;
            L->length--;
        }
    } else if (L->length == 0){
        printf("List Error: calling delete() on an empty List\n");
        exit(EXIT_FAILURE);
    } else {
        printf("List Error: calling delete() without a cursor set\n");
        exit(EXIT_FAILURE);
    }
}
// Other Operations ------------------------------------------------------------------
void printList(FILE* out, List L){
    int curr = L->cursorPos;
    moveFront(L);
    while (L->cursorPos != -1){
        fprintf(out, "%d ", get(L));
        moveNext(L);
    }
    if (curr == -1){
        L->cursor = NULL;
        L->cursorPos = -1;
    } else {
        moveFront(L);
        for (int i = 0; i < curr; ++i) {
            moveNext(L);
        }
    }
}

void printList1(List L){
    moveFront(L);
    for (int i = 0; i < length(L); ++i) {
        printf("%d\n", get(L));
        moveNext(L);
    }
}
