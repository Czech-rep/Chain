#include <iostream>

#include "chain.h"
#include "testing.h"

int main()
{
    TestChain test;
    test.execute();

    TestCustom test2;
    test2.execute();
/*
    ClosedChain<int>* sample = new ClosedChain<int>;
    int a=9,b=27,c=77,d=123;
    std::cout<<*sample<<std::endl;
    *sample += a;
    std::cout<<*sample<<std::endl;
    *sample += b;
    *sample += c;
    *sample += d;
    std::cout<<"start"<<std::endl;
    std::cout<<*sample<<std::endl;
    //std::cout<<sample->get_nth(1)->get_anchor()->get_anchor()->get_value() <<std::endl;

    std::cout<<(*sample->get_nth(0))<<std::endl;
    sample->wipeout(1);
    std::cout<<*sample<<std::endl;
    sample->wipeout(0);

    sample->wipeout(0);

    std::cout<<*sample<<std::endl;
    std::cout<<" to bvyla lista " <<std::endl;
*/
    std::cout << "===   program executed " << std::endl;
    return 0;
}





