#include <iostream>
#include <fstream>
#include <string>
#include "BigInteger.h"

int main(int argc, char* argv[]){
    if(argv[3] != nullptr){
        std::cout << "Too many arguments" << std::endl;
        exit(1);
    }
    int i = 0;
    std::string in[3];
    std::ifstream file(argv[1]);
    std::string line;
    while (std::getline(file, line)){
        in[i] = line;
        i++;
    }
    file.close();
    std::ofstream file1(argv[2]);
    BigInteger A = BigInteger(in[0]);
    BigInteger B = BigInteger(in[2]);
    file1 << A << std::endl << std::endl;
    file1 << B << std::endl << std::endl;
    file1 << A + B << std::endl << std::endl;
    file1 << A - B << std::endl << std::endl;
    file1 << A - A << std::endl << std::endl;
    file1 << ((A*3) - (2*B)) << std::endl << std::endl; //
    file1 << A * B << std::endl << std::endl;
    file1 << A * A << std::endl << std::endl;
    file1 << B * B << std::endl << std::endl;
    file1 << ((9 * (A*A*A*A)) + (16 * (B*B*B*B*B))) << std::endl;
    file1.close();
    return 0;
}
