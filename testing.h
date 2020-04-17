#ifndef TESTING_H_INCLUDED
#define TESTING_H_INCLUDED

#include <cassert>
#include "chain.h"


class TestChain{
    ClosedChain<int>* sample = new ClosedChain<int>;

public:
    TestChain();
    ~TestChain();

    void execute();
    void test_fill_length();
    void test_delete();
    void test_empty();
    void test_compare();
    void test_inject();
    void test_printing();

    void test_out_of_range();

};

// =========================== IMPLEMENTATION =========================== \\



TestChain::TestChain(){
    std::cout << "testing instance initialized" << std::endl;
}
void TestChain::execute(){
    test_empty();
    test_fill_length();
    test_delete();
    test_compare();
    test_inject();
    test_printing();
    test_out_of_range();

    std::cout << "all tests succeeded" << std::endl << std::endl;
}

void TestChain::test_empty(){
    assert( sample->is_blanc() == 1 );
    std::cout << "-> test_empty succeeded" << std::endl;
}
void TestChain::test_fill_length(){
    int a=9,b=27,c=77,d=123;
    *sample += a;
    *sample += b;
    *sample += c;
    *sample += d;
    assert( sample->get_length() == 4 );
    std::cout << "-> test_fill_length succeeded" << std::endl;
}
void TestChain::test_delete(){
    sample->wipeout(0);
    assert( sample->get_nth(0)->get_value() == 27 );
    std::cout << "-> test_delete succeeded" << std::endl;
}
void TestChain::test_compare(){
    ClosedChain<int>* other = new ClosedChain<int>;
    int q=27, w=77, e=123;
    *other += q;
    *other += w;
    *other += e;
    assert( *sample == *other );
    delete other;
    std::cout << "-> test_compare succeeded" << std::endl;
}
void TestChain::test_inject(){
    int t=49;
    sample->inject(0, t);
    assert( sample->get_nth(0)->get_value() == 49 );
    std::cout << "-> test_inject succeeded" << std::endl;
}
void TestChain::test_printing(){
    std::cout <<*sample;
    std::cout << "-> test_printing succeeded" << std::endl;
}

TestChain::~TestChain(){
    delete sample;
}

void TestChain::test_out_of_range(){
    try{
        sample->pick_predecessor(99);
    }
    catch (exceeded_scope){
        std::cout << "-> test_out_of_range succeeded" << std::endl;
        return;
    }
    std::cout << "-> test_out_of_range failed" << std::endl;
}

/*
co musze zmienic
test jakos tak zeby nie byl templatem. i testowal moj wlasny typ
 i zeby nie zapisywac do chaina statycznych obiektow
 poczytaj o throw i smart pointer
 sprawdz co robia metody dla pustej listy
 i assert jesno na test*/





#endif // TESTING_H_INCLUDED
