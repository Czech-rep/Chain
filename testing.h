#ifndef TESTING_H_INCLUDED
#define TESTING_H_INCLUDED

#include <cassert>
#include <memory>
#include "chain.h"


class TestChain{
    //ClosedChain<int>* sample = new ClosedChain<int>;
    std::unique_ptr<ClosedChain<int>> sample = std::make_unique<ClosedChain<int>>();
        //unique smart ptr - istnieje tylko w tej klasie testującej. nie wolno kopiowac, przypisywać
        //automatycznie sie usuwa wiec nie potrzeba definiowac destruktora
public:
    TestChain();
    //~TestChain();

    void execute();
    void test_fill_length();
    void test_delete();
    void test_empty();
    void test_compare();
    void test_inject();
    void test_printing();

    void test_exceptions();

};

// =========================== IMPLEMENTATION =========================== \\



TestChain::TestChain(){
    std::cout << "testing instance initialized" << std::endl;
}
/*TestChain::~TestChain(){
    //delete sample;
}*/

void TestChain::execute(){
    test_empty();
    test_fill_length();
    test_delete();
    test_compare();
    test_inject();
    test_printing();
    test_exceptions();

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
    //ClosedChain<int>* other = new ClosedChain<int>;
    std::unique_ptr<ClosedChain<int>> other = std::make_unique<ClosedChain<int>>();     //tu dziala rowniez dla statycznie zdefiniowanego closedChain - dlaczego tak nie zrobić?
    //ClosedChain<int> other;
    int q=27, w=77;
    *other += q;
    *other += w;
    *other += int(123);                                                     //inna metoda tworzenia - mozliwe bo dodajac kopiujemy
    assert( *sample == *other );
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

void TestChain::test_exceptions(){
    try{
        sample->pick_predecessor(99);
    }
    catch (ClosedChain<int>::ExceededScope theException){
        theException.print_message();
        std::cout << "-> test_out_of_range succeeded 1/2" << std::endl;
                                                              //----------------------- Czy to dozwolone wyjœciue z funkcji void? - dotycvzyło return
    }
    try{
        sample->pick_predecessor(-5);
    }
    //catch (ClosedChain<int>::Error theException){
    catch (ClosedChain<int>::IncorrectInput theException){
        theException.print_message();
        std::cout << "-> test_out_of_range succeeded 2/2" << std::endl;
    }
    //std::cout << "-> test_out_of_range failed" << std::endl;                                      ciekawi mnie jak spiąć te wszystkie testy = mnożyć boole?
}

/*
co musze zmienic
 poczytaj o throw i smart pointer
 sprawdz co robia metody dla pustej listy
*/




#endif // TESTING_H_INCLUDED
