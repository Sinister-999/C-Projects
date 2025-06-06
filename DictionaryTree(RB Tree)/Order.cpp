/***
* Jestin Baath
* jsbaath
* 2024 Fall CSE101 PA7
* Order.cpp
* Client for Dictionary ADT
***/
#include <iostream>
#include <fstream>
#include <string>
#include "Dictionary.h"

int main(int argc, char* argv[]){
    if(argv[3] != nullptr){
        std::cout << "Too many or Too few arguments" << std::endl;
        exit(1);
    }
    Dictionary A;
    int i = 1;
    std::ifstream file(argv[1]);
    std::string line;
    while (std::getline(file, line)){
        A.setValue(line, i);
        i++;
    }

    file.close();
    std::ofstream file1(argv[2]);
    file1 << A;
    std::string a = A.pre_string();
    a.pop_back();
    file1 << a;
    file1.close();
    return 0;
}