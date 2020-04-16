#ifndef TESTING_H_INCLUDED
#define TESTING_H_INCLUDED

#include "chain.h"

template<typename T>
class TestChain{
    ClosedChain<T>* sample = nullptr;

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

// =========================== IMPLEMENTATION =========================== \\


template<typename T>
TestChain<T>::TestChain(){
    init();
    std::cout << "testing instance initialized" << std::endl;
}
template<typename T>
void TestChain<T>::init(){
    sample = new ClosedChain<T>;
}
template<typename T>
void TestChain<T>::execute_all(){
    test_empty();
    test_fill_length_match();
    test_delete();
    test_compare();
    test_inject();
    test_printing();

    std::cout << "all tests succeeded" << std::endl;
}


template<typename T>
void TestChain<T>::test_empty(){
    assert( sample->is_blanc() == 1 );
    *sample += new UniBox<T>(2);
    assert( sample->is_blanc() == 0 );
    std::cout << "-> test_empty succeeded" << std::endl;
}
template<typename T>
void TestChain<T>::test_fill_length_match(){
    *sample += new UniBox<T>(9);
    *sample += new UniBox<T>(27);
    *sample += new UniBox<T>(77);
    *sample += new UniBox<T>(123);

    assert( sample->get_length() == 5 );
    assert( sample->get_nth(0)->get_value() == 2 );
    assert( sample->get_nth(4)->get_value() == 123 );
    std::cout << "-> test_fill_length_match succeeded" << std::endl;
}
template<typename T>
void TestChain<T>::test_delete(){
    sample->wipeout(4);
    sample->wipeout(0);
    assert( sample->get_length() == 3 );
    assert( sample->get_nth(0)->get_value() == 9 );
    assert( sample->get_nth(2)->get_value() == 77 );
    std::cout << "-> test_delete succeeded" << std::endl;
}
template<typename T>
void TestChain<T>::test_compare(){
    ClosedChain<T> other;
    UniBox<T> q(9), w(27), e(77);
    other += &q;
    other += &w;
    other += &e;
    assert( *sample == other );
    other.wipeout(0);
    assert( !(*sample == other) );
    other.~ClosedChain();
    std::cout << "-> test_compare succeeded" << std::endl;
}
template<typename T>
void TestChain<T>::test_inject(){
    assert( sample->get_nth(1)->get_value() == 27 );
    UniBox<T> *q = new UniBox<T>(49);
    //UniBox q(49                                   dziwnie sie dzieje jak stworzymy element w miejscu - po zakonczeniu funkcji nie znika
    sample->inject(1, q);
    assert( sample->get_nth(1)->get_value() == 49 );
    assert( sample->get_nth(2)->get_value() == 27 );
        assert( sample->get_nth(0)->get_value() == 9 );
        UniBox<T> *w = new UniBox<T>(50);
        sample->inject(0, w);
        assert( sample->get_nth(0)->get_value() == 50 );
    UniBox<T> *e = new UniBox<T>(500);
    sample->inject(5, e);
    assert( sample->get_nth(5)->get_value() == 500 );
    //std::cout <<*sample;
    //std::cout << sample->get_length() << std::endl;
    //std::cout << "last elem fun: " << sample->get_nth(5)->get_value() << std::endl;
    std::cout << "-> test_inject succeeded" << std::endl;
}
template<typename T>
void TestChain<T>::test_printing(){
    std::cout <<*sample;
    std::cout << "-> test_printing succeeded" << std::endl;
    //std::cout << "last elem: " << (sample->pick_predecessor(sample->get_length()))->get_value() << std::endl;
    //std::cout << "last elem: " << sample->get_nth(4)->get_value() << std::endl;
}
//duuuuuze pytanie, co sie dzieje dlaczego teraz dziala mimo ze obiekty e(500) i w(50) powinny zostaæ ununiete?

template<typename T>
TestChain<T>::~TestChain(){
    sample->~ClosedChain();
}




#endif // TESTING_H_INCLUDED
