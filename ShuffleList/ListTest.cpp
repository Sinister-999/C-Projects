/***
* Jestin Baath
* jsbaath
* 2024 Fall CSE101 PA5
* ListTest.cpp
* Testing Client for List ADT
***/
#include <iostream>
#include "List.h"

using namespace std;

int main(){
    List A;
    List B;
    A.insertBefore(1);
    A.insertBefore(2);
    A.insertBefore(3);
    B.insertBefore(4);
    B.insertBefore(5);
    B.insertBefore(6);
    if (A.findNext(99) != -1)
        std::cout << "fail" << std::endl;
    if (A.position() != A.length())
        std::cout << "fail" << std::endl;

    A.moveFront();
    if (A.findNext(1) != 4)
        std::cout << "fail" << std::endl;
    if (A.findNext(1) != 6)
        std::cout << "fail" << std::endl;
    if (A.findNext(1) != -1)
        std::cout << "fail" << std::endl;

    A.moveFront();
    A.cleanup();
    if (A.findNext(1) != 3)
        std::cout << "fail" << std::endl;
    if (A.findNext(1) != -1)
        std::cout << "fail" << std::endl;

    return 0;

}