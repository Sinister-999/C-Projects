/***
* Jestin Baath
* jsbaath
* 2024 Fall CSE101 PA6
* List.cpp
* List ADT
***/
#include <iostream>
#include "List.h"

List::Node::Node(ListElement x) {
    data = x;
    next = nullptr;
    prev = nullptr;
}

List::List() {
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

List::List(const List& L) {
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = nullptr;
    afterCursor = nullptr;
    pos_cursor = 0;
    num_elements = 0;

    Node* curr = L.frontDummy->next;
    this->moveFront();
    while (curr != L.backDummy){
        this->insertAfter(curr->data);
        curr = curr->next;
        this->moveNext();
    }
}

List::~List(){
    this->clear();
    delete frontDummy;
    delete backDummy;
}

int List::length() const {
    return (num_elements);
}

ListElement List::front() const {
    if (num_elements > 0){
        return (frontDummy->next->data);
    }
}

ListElement List::back() const {
    if (num_elements > 0){
        return (backDummy->prev->data);
    }
}

int List::position() const {
    return (pos_cursor);
}

ListElement List::peekNext() const {
    if (pos_cursor < num_elements){
        return (afterCursor->data);
    }
}

ListElement List::peekPrev() const {
    if (pos_cursor > 0) {
        return (beforeCursor->data);
    }
}

void List::clear(){
    if (this->length() == 0) {
        return;
    } else {
        this->moveFront();
        while (this->length() != 0){
            this->eraseAfter();
        }
    }
}

void List::moveFront() {
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
}

void List::moveBack() {
    pos_cursor = num_elements;
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
}

ListElement List::moveNext() {
    if (pos_cursor < num_elements){
        pos_cursor++;
        afterCursor = afterCursor->next;
        beforeCursor = beforeCursor->next;
        return (beforeCursor->data);
    }
}

ListElement List::movePrev() {
    if (pos_cursor > 0){
        pos_cursor--;
        afterCursor = afterCursor->prev;
        beforeCursor = beforeCursor->prev;
        return (afterCursor->data);
    }
}

void List::insertAfter(ListElement x) {
    if(num_elements == 0){
        Node* node = new Node(x);
        frontDummy->next = node;
        backDummy->prev = node;
        node->prev = frontDummy;
        node->next = backDummy;
        afterCursor = node;
        beforeCursor = frontDummy;
        num_elements++;
    } else if(pos_cursor == num_elements) {
        Node* node = new Node(x);
        backDummy->prev = node;
        beforeCursor->next = node;
        node->prev = beforeCursor;
        node->next = backDummy;
        afterCursor = node;
        num_elements++;
    }else {
        Node *node = new Node(x);
        beforeCursor->next = node;
        afterCursor->prev = node;
        node->next = afterCursor;
        node->prev = beforeCursor;
        afterCursor = node;
        num_elements++;
    }
}

void List::insertBefore(ListElement x) {
    if(num_elements == 0){
        Node* node = new Node(x);
        frontDummy->next = node;
        backDummy->prev = node;
        node->prev = frontDummy;
        node->next = backDummy;
        beforeCursor = node;
        afterCursor = backDummy;
        pos_cursor++;
        num_elements++;
    } else if(pos_cursor == 0) {
        Node* node = new Node(x);
        frontDummy->next = node;
        afterCursor->prev = node;
        node->prev = frontDummy;
        node->next = afterCursor;
        beforeCursor = node;
        pos_cursor++;
        num_elements++;
    }else {
        Node *node = new Node(x);
        beforeCursor->next = node;
        afterCursor->prev = node;
        node->next = afterCursor;
        node->prev = beforeCursor;
        beforeCursor = node;
        pos_cursor++;
        num_elements++;
    }
}

void List::setAfter(ListElement x) {
    if (pos_cursor < num_elements){
        afterCursor->data = x;
    }
}

void List::setBefore(ListElement x) {
    if (pos_cursor > 0){
        beforeCursor->data = x;
    }
}

void List::eraseAfter() {
    if (pos_cursor < num_elements){
        if(num_elements == 1){
            delete afterCursor;
            backDummy->prev = frontDummy;
            frontDummy->next = backDummy;
            afterCursor = backDummy;
            beforeCursor = frontDummy;
            pos_cursor = 0;
            num_elements--;
        } else{
            beforeCursor->next = afterCursor->next;
            afterCursor->next->prev = beforeCursor;
            delete afterCursor;
            afterCursor = beforeCursor->next;
            num_elements--;
        }
    }
}

void List::eraseBefore() {
    if (pos_cursor > 0){
        if (num_elements == 1){
            delete beforeCursor;
            backDummy->prev = frontDummy;
            frontDummy->next = backDummy;
            afterCursor = backDummy;
            beforeCursor = frontDummy;
            pos_cursor = 0;
            num_elements--;
        } else{
            afterCursor->prev = beforeCursor->prev;
            beforeCursor->prev->next = afterCursor;
            delete beforeCursor;
            beforeCursor = afterCursor->prev;
            num_elements--;
            pos_cursor--;
        }
    }
}

int List::findNext(ListElement x) {
    for (int i = pos_cursor; i < num_elements; ++i) {
        if (afterCursor->data != x){
            this->moveNext();
            continue;
        } else {
            this->moveNext();
            return(pos_cursor);
        }
    }
    pos_cursor = num_elements;
    return (-1);
}

int List::findPrev(ListElement x) {
    for (int i = pos_cursor; i > 0; --i) {
        if (beforeCursor->data != x){
            this->movePrev();
            continue;
        } else{
            this->movePrev();
            return (pos_cursor);
        }
    }
    pos_cursor = 0;
    return (-1);
}

void List::cleanup() {
    int pos = this->pos_cursor;
    this->moveFront();
    int index = 0;
    while (index < this->length()) {
        int pos1 = index+1;
        int curr = this->peekNext();
        this->moveNext();
        while (pos1 < this->length()) {
            if (this->peekNext() == curr) {
                this->eraseAfter();
                if (pos1 < pos){
                    pos--;
                }
            } else {
                this->moveNext();
                pos1++;
            }
        }
        index++;
        this->moveFront();
        for (int i = 0; i < index; ++i) {
            this->moveNext();
        }
    }

    this->moveFront();
    for (int i = 0; i < pos; ++i) {
        moveNext();
    }
}

List List::concat(const List& L) const{
    List out;
    Node* TCurr = this->frontDummy->next;
    while (TCurr != this->backDummy){
        out.insertBefore(TCurr->data);
        TCurr = TCurr->next;
    }

    Node* LCurr = L.frontDummy->next;
    while (LCurr != L.backDummy){
        out.insertBefore(LCurr->data);
        LCurr = LCurr->next;
    }
    out.moveFront();
    return out;
}

std::string List::to_string() const {
    std::string test = "hello";
    return (test);
}

bool List::equals(const List &R) const {
    if (this->length() != R.length()){
        return false;
    }
    List::Node* Tcurr = this->frontDummy->next;
    List::Node* Rcurr = R.frontDummy->next;
    while (Rcurr != R.backDummy){
        if (Rcurr->data != Tcurr->data){
            return false;

        } else{
            Tcurr = Tcurr->next;
            Rcurr = Rcurr->next;
            continue;
        }
    }
    return true;
}

std::ostream& operator<<( std::ostream& stream, const List& L ){
    List::Node* Curr = L.frontDummy->next;
    while (Curr != L.backDummy){
        stream << Curr->data;
        if (Curr->next != L.backDummy){
            stream << " ";
        }
        Curr = Curr->next;
    }
    return stream;
}

bool operator==(const List& A, const List& B ){
    if (A.length() != B.length()){
        return false;
    }
    List::Node* Acurr = A.frontDummy->next;
    List::Node* Bcurr = B.frontDummy->next;
    while (Acurr != A.backDummy){
        if (Bcurr->data != Acurr->data){
            return false;

        } else{
            Acurr = Acurr->next;
            Bcurr = Bcurr->next;
            continue;
        }
    }
    return true;
}

List& List::operator=(const List &L) {
    if (this == &L){
        return *this;
    }
    this->clear();

    Node* curr = L.frontDummy->next;
    this->moveFront();
    while (curr != L.backDummy){
        this->insertAfter(curr->data);
        curr = curr->next;
        this->moveNext();
    }
    return *this;
}




