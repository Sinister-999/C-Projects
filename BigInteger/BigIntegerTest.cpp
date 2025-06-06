#include <iostream>
#include "BigInteger.h"
#include "List.h"

int main(void ){
    BigInteger A = BigInteger("+111122223333");
    BigInteger B = BigInteger("+111122223333");

    BigInteger C = A - B;
    if (C.sign() != 0)
        std::cout << "fail" << std::endl;

    // pos - pos < 0
    B = BigInteger("121122223333");
    BigInteger D = BigInteger("-10000000000");
    C = A - B;
    if (C.sign() != -1)
        std::cout << "fail" << std::endl;
    if (!(C == D))
        std::cout << "fail" << std::endl;

    // pos - pos > 0
    B = BigInteger("101122223333");
    D = BigInteger("10000000000");
    C = A - B;
    if (C.sign() != 1)
        std::cout << "fail" << std::endl;
    if (!(C == D))
        std::cout << "fail" << std::endl;

    // pos - neg = pos
    B.negate();
    D = BigInteger("212244446666");
    C = A - B;
    if (C.sign() != 1)
        std::cout << "fail" << std::endl;
    if (!(C == D))
        std::cout << "fail" << std::endl;

    // neg - pos = neg
    D.negate();
    C = B - A;
    if (C.sign() != -1)
        std::cout << "fail" << std::endl;
    if (!(C == D))
        std::cout << "fail" << std::endl;



    return 0;

}
