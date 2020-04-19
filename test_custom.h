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
    std::string get_name() const {     return first_name;  }
    bool operator==(const Person &other) const{
        if( first_name==other.first_name && last_name==other.last_name && number==other.number)
            return true;
        return false;
    }
    bool operator!=(const Person &other) const{
        if( first_name!=other.first_name || last_name!=other.last_name || number!=other.number)
            return true;
        return false;
    }
};
std::ostream& operator<<(std::ostream& os, const Person& content){
     os << content.get_name();
     return os;
}


class TestCustom{
    //ClosedChain<Person>* sample = new ClosedChain<Person>;
    std::unique_ptr<ClosedChain<Person>> sample = std::make_unique<ClosedChain<Person>>();


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

    void test_exceptions();

};

// =========================== IMPLEMENTATION =========================== \\



TestCustom::TestCustom(){
    std::cout << "custom class testing instance initialized" << std::endl;
}
TestCustom::~TestCustom(){
    //delete sample;
}
void TestCustom::execute(){
    test_empty();
    test_fill_length();
    test_delete();
    test_compare();
    test_inject();
    test_printing();
    test_exceptions();

    std::cout << "all tests succeeded" << std::endl << std::endl;
}

void TestCustom::test_empty(){
    assert( sample->is_blanc() == 1 );
    std::cout << "-> test_empty succeeded" << std::endl;
}
void TestCustom::test_fill_length(){
    Person* a = new Person("Adam", "Czech", 67676237);
    Person b("franek","k",5);
    Person c("wojtek", "cc",6);
    *sample += *a;
    *sample += b;
    *sample += Person("wojtek", "cc", 6);
    assert( sample->get_length() == 3 );
    std::cout << "-> test_fill_length succeeded" << std::endl;
}
void TestCustom::test_delete(){
    sample->wipeout(0);
    assert( sample->get_nth(0)->get_value().get_name() == "franek" );
    std::cout << "-> test_delete succeeded" << std::endl;
}
void TestCustom::test_compare(){
    ClosedChain<Person> other;
    Person q("franek","k",5);
    Person w("wojtek", "cc",6);
    other += q;
    other += w;
    assert( *sample == other );
    std::cout << "-> test_compare succeeded" << std::endl;
}
void TestCustom::test_inject(){
    Person pp("karol","ww",21);
    sample->inject(0, pp);
    assert( sample->get_nth(0)->get_value() == Person("karol","ww",21) );
    std::cout << "-> test_inject succeeded" << std::endl;
}
void TestCustom::test_printing(){
    std::cout <<*sample;
    std::cout << "-> test_printing succeeded" << std::endl;
}
void TestCustom::test_exceptions(){
    try{
        sample->pick_predecessor(99);
    }
    catch (ClosedChain<Person>::ExceededScope theException){
        theException.print_message();
        std::cout << "-> test_out_of_range succeeded 1/2" << std::endl;
    }
    try{
        sample->pick_predecessor(-5);
    }
    //catch (ClosedChain<int>::Error theException){
    catch (ClosedChain<Person>::IncorrectInput theException){
        theException.print_message();
        std::cout << "-> test_out_of_range succeeded 2/2" << std::endl;
    }
}


#endif // TEST_CUSTOM_H_INCLUDED
