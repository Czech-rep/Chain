#include <iostream>

#include "chain.h"
#include "testing.h"

int main()
{
    TestChain test;
    test.execute();

    TestCustom test2;
    test2.execute();



    std::cout << "===   program executed " << std::endl;
    return 0;
}





