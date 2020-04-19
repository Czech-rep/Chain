#include <iostream>

#include "chain.h"
#include "testing.h"
#include "test_custom.h"

int main()
{
    TestChain test;
    test.execute();

    TestCustom test2;
    test2.execute();

    /*ClosedChain<int>* sample = new ClosedChain<int>;
    int a=9,b=27,c=77,d=123;
    *sample += a;
    *sample += b;
    *sample += c;
    *sample += d;

    //std::cout<<(*sample->get_nth(2))<<std::endl;
    auto kk = sample->get_nth(96);

    std::cout<<*sample<<std::endl;
    std::cout<<" to bvyla lista " <<std::endl;
*/
    std::cout << "===   program executed " << std::endl;
    return 0;
}





