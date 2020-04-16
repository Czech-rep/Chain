#include "testing.h"
#include "chain.h"

#include <iostream>
#include <cassert>


TestChain::TestChain(){
    init();
    std::cout << "testing instance initialized" << std::endl;
}
void TestChain::init(){
    sample = new ClosedChain;
}
void TestChain::execute_all(){
    test_empty();
    test_fill_length_match();
    test_delete();
    test_compare();
    test_inject();
    test_printing();

    std::cout << "all tests succeeded" << std::endl;
}


void TestChain::test_empty(){
    assert( sample->is_blanc() == 1 );
    *sample += new UniBox(2);
    assert( sample->is_blanc() == 0 );
    std::cout << "-> test_empty succeeded" << std::endl;
}
void TestChain::test_fill_length_match(){
    *sample += new UniBox(9);
    *sample += new UniBox(27);
    *sample += new UniBox(77);
    *sample += new UniBox(123);

    assert( sample->get_length() == 5 );
    assert( sample->get_nth(0)->get_value() == 2 );
    assert( sample->get_nth(4)->get_value() == 123 );
    std::cout << "-> test_fill_length_match succeeded" << std::endl;
}
void TestChain::test_delete(){
    sample->wipeout(4);
    sample->wipeout(0);
    assert( sample->get_length() == 3 );
    assert( sample->get_nth(0)->get_value() == 9 );
    assert( sample->get_nth(2)->get_value() == 77 );
    std::cout << "-> test_delete succeeded" << std::endl;
}
void TestChain::test_compare(){
    ClosedChain other;
    UniBox q(9), w(27), e(77);
    other += &q;
    other += &w;
    other += &e;
    assert( *sample == other );
    other.wipeout(0);
    assert( !(*sample == other) );
    other.~ClosedChain();
    std::cout << "-> test_compare succeeded" << std::endl;
}
void TestChain::test_inject(){
    assert( sample->get_nth(1)->get_value() == 27 );
    UniBox *q = new UniBox(49);
    //UniBox q(49                                   dziwnie sie dzieje jak stworzymy element w miejscu - po zakonczeniu funkcji nie znika
    sample->inject(1, q);
    assert( sample->get_nth(1)->get_value() == 49 );
    assert( sample->get_nth(2)->get_value() == 27 );
        assert( sample->get_nth(0)->get_value() == 9 );
        UniBox *w = new UniBox(50);
        sample->inject(0, w);
        assert( sample->get_nth(0)->get_value() == 50 );
    UniBox *e = new UniBox(500);
    sample->inject(5, e);
    assert( sample->get_nth(5)->get_value() == 500 );
    //std::cout <<*sample;
    //std::cout << sample->get_length() << std::endl;
    //std::cout << "last elem fun: " << sample->get_nth(5)->get_value() << std::endl;
    std::cout << "-> test_inject succeeded" << std::endl;
}
void TestChain::test_printing(){
    std::cout <<*sample;
    std::cout << "-> test_printing succeeded" << std::endl;
    //std::cout << "last elem: " << (sample->pick_predecessor(sample->get_length()))->get_value() << std::endl;
    //std::cout << "last elem: " << sample->get_nth(4)->get_value() << std::endl;
}
//duuuuuze pytanie, co sie dzieje dlaczego teraz dziala mimo ze obiekty e(500) i w(50) powinny zosta ununiete?
TestChain::~TestChain(){
    sample->~ClosedChain();
}









