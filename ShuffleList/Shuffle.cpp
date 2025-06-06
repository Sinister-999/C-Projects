/***
* Jestin Baath
* jsbaath
* 2024 Fall CSE101 PA5
* Shuffle.cpp
* Client file for PA5
***/
#include <iostream>
#include "List.h"

void shuffle(List& D){
    List Left;
    List Right;
    int length = D.length();
    bool even = true;
    if(length == 1){
        return;
    }
    if ((length % 2) != 0){
        even = false;
        length--;
    }
    int half = length/2;
    D.moveFront();
    while (D.position() != half){
        Left.insertBefore(D.peekNext());
        D.moveNext();
    }
    while (D.position() != length){
        Right.insertBefore(D.peekNext());
        D.moveNext();
    }
    if (!even){
        Right.insertBefore(D.peekNext());
        D.moveNext();
    }
    length = D.length();
    D.clear();
    Left.moveFront(); Right.moveFront();
    for (int i = 1; i <= length; ++i) {
        if (i % 2 != 0){
            D.insertBefore(Right.peekNext());
            Right.moveNext();
        } else{
            D.insertBefore(Left.peekNext());
            Left.moveNext();
        }
    }
}

int main(int argc, char* argv[]){
    if (argc > 2 || argc < 2){
        std::cout << "Too many Arguments" << std::endl;
        exit(1);
    }
    int size = std::stoi(argv[1]);
    List A;
    List B;
    std::cout << "deck size       shuffle count\n------------------------------" << std::endl;
    for (int i = 0; i < size; ++i) {
        int a = i + 1;
        A.insertBefore(i);
        B.insertBefore(i);
        int shuffles = 1;
        shuffle(A);
        while (!(A.equals(B))){
            shuffle(A);
            shuffles++;
            continue;
        }
        if (a < 100 && a > 9) {
            std::cout << " " << a << "              " << shuffles;
        } else if (a < 1000 && a > 99){
            std::cout << " " << a << "             " << shuffles;
        } else if (a < 10000 && a > 999){
            std::cout << " " << a << "            " << shuffles;
        } else if (a < 100000 && a > 9999){
            std::cout << " " << a << "           " << shuffles;
        } else {
            std::cout << " " << a << "               " << shuffles;
        }
        std::cout << "\n";

        continue;
    }
    return 0;
}