#ifndef TESTING_H_INCLUDED
#define TESTING_H_INCLUDED

#include "chain.h"

class TestChain{
    ClosedChain* sample = nullptr;

public:
    TestChain();
    void init();
    void execute_all();
    ~TestChain();

    void test_fill_length_match();
    void test_delete();
    void test_empty();
    void test_compare();
    void test_inject();
    void test_printing();

};






#endif // TESTING_H_INCLUDED
