#ifndef TEST_CUSTOM_H_INCLUDED
#define TEST_CUSTOM_H_INCLUDED

#include <cassert>
#include "chain.h"


class Person{
    std::string first_name, last_name;
    int number;
public:
    Person(std::string _first_name, std::string _last_name, int _number):
        first_name(_first_name), last_name(_last_name), number(_number) {}
    bool operator==(const Person &other) const{
        if( first_name==other.first_name && last_name==other.last_name && number==other.number)
            return true;
        return false;
    }

};


class TestCustom{
    ClosedChain<Person>* sample = new ClosedChain<Person>;

public:
    TestCustom();
    ~TestCustom();

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



TestCustom::TestCustom(){
    std::cout << "custom class testing instance initialized" << std::endl;
}
void TestCustom::execute(){
    test_empty();
    test_fill_length();
    /*test_delete();
    test_compare();
    test_inject();
    test_printing();
    test_out_of_range();

    std::cout << "all tests succeeded" << std::endl;*/
}

void TestCustom::test_empty(){
    assert( sample->is_blanc() == 1 );
    std::cout << "-> test_empty succeeded" << std::endl;
}
void TestCustom::test_fill_length(){
    Person* a = new Person("Adam", "Czech", 67676237);
    UniBox<Person>* b ;//= new UniBox<Person>(*a);
    UniBox<Person> c(*a);
    b = &c;
    *sample += (b);
    /* *sample += new UniBox<Person>(27);
    *sample += new UniBox<Person>(77);
    *sample += new UniBox<Person>(123);
    assert( sample->get_length() == 4 );
    std::cout <<*sample;
    std::cout << "-> test_fill_length succeeded" << std::endl;*/
}/*
void TestCustom::test_delete(){
    sample->wipeout(0);
    assert( sample->get_nth(0)->get_value() == 27 );
    std::cout << "-> test_delete succeeded" << std::endl;
}
void TestCustom::test_compare(){
    ClosedChain<int>* other = new ClosedChain<int>;
    *other += new UniBox<int>(27);
    *other += new UniBox<int>(77);
    *other += new UniBox<int>(123);
    assert( *sample == *other );
    delete other;
    std::cout << "-> test_compare succeeded" << std::endl;
}
void TestCustom::test_inject(){
    std::cout <<*sample;
    UniBox<int> *q = new UniBox<int>(49);
    sample->inject(0, q);
    std::cout <<*sample;
    assert( sample->get_nth(0)->get_value() == 49 );
    std::cout << "-> test_inject succeeded" << std::endl;
}
void TestCustom::test_printing(){
    std::cout <<*sample;
    std::cout << "-> test_printing succeeded" << std::endl;
}


void TestCustom::test_out_of_range(){
    try{
        sample->pick_predecessor(99);
    }
    catch (exceeded_scope){
        std::cout << "-> test_out_of_range succeeded" << std::endl;
        return;
    }
    std::cout << "-> test_out_of_range failed" << std::endl;
}
*/
TestCustom::~TestCustom(){
    delete sample;
}
#endif // TEST_CUSTOM_H_INCLUDED
