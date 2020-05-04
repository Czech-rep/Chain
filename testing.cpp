#include <cassert>
#include <memory>
#include "testing.h"
#include "chain.h"


TestChain::TestChain(){
    std::cout << "integer testing instance initialized" << std::endl;
}
void TestChain::execute(){
    std::cout << "-> executing test_empty" << std::endl;
    test_empty();
    std::cout << "-> executing test_fill_length" << std::endl;
    test_fill_length();
    std::cout << "-> executing test_delete" << std::endl;
    test_delete();
    std::cout << "-> executing test_compare" << std::endl;
    test_compare();
    std::cout << "-> executing test_inject" << std::endl;
    test_inject();
    std::cout << "-> executing test_exceptions" << std::endl;
    test_exceptions();
    //std::cout << *sample << std::endl;
    std::cout << "all tests succeeded" << std::endl << std::endl;
}
void TestChain::test_empty(){
    assert( sample->is_blanc() == 1 );
}
void TestChain::test_fill_length(){
    int a=9,b=27,c=77,d=123;
    *sample += a;
    *sample += b;
    *sample += c;
    *sample += d;
    assert( sample->get_length() == 4 );
}
void TestChain::test_delete(){
    sample->wipeout(0);
    assert( sample->print_content(0) == 27 );
}
void TestChain::test_compare(){
    std::unique_ptr<ClosedChain<int>> other = std::make_unique<ClosedChain<int>>();
    int q=27, w=77;
    *other += q;
    *other += w;
    *other += int(123);                                                     //inna metoda tworzenia - mozliwe bo dodajac kopiujemy
    assert( *sample == *other );
}
void TestChain::test_inject(){
    int t=49;
    sample->inject(0, t);
    assert( sample->print_content(0) == 49 );
}
void TestChain::test_exceptions(){
    int i=0;
    try{
        sample->print_content(99);
    }
    catch (ExceededScope ){
        i++;
    }
    try{
        sample->print_content(-5);
    }
    catch (IncorrectInput ){
        i++;
    }
    assert( i == 2 );
}

//========================implementation of TestCustom========================//

bool TestCustom::Person::operator==(const Person &other) const{
    if( first_name==other.first_name && last_name==other.last_name && number==other.number)
        return true;
    return false;
}
bool TestCustom::Person::operator!=(const Person &other) const{
    if( first_name!=other.first_name || last_name!=other.last_name || number!=other.number)
        return true;
    return false;
}
std::ostream& operator<<(std::ostream& os, const TestCustom::Person& content){
     os << content.get_name();
     return os;
}

TestCustom::TestCustom(){
    std::cout << "custom class testing instance initialized" << std::endl;
}
void TestCustom::execute(){
    std::cout << "-> executing test_empty" << std::endl;
    test_empty();
    std::cout << "-> executing test_fill_length" << std::endl;
    test_fill_length();
    std::cout << "-> executing test_delete" << std::endl;
    test_delete();
    std::cout << "-> executing test_compare" << std::endl;
    test_compare();
    std::cout << "-> executing test_inject" << std::endl;
    test_inject();
    std::cout << "-> executing test_exceptions" << std::endl;
    test_exceptions();
    //std::cout << *sample << std::endl;
    std::cout << "all tests succeeded" << std::endl << std::endl;
}
void TestCustom::test_empty(){
    assert( sample->is_blanc() == 1 );
}
void TestCustom::test_fill_length(){
    Person* a = new Person("Adam", "Czech", 67676237);
    Person b("franek","k",5);
    Person c("wojtek", "cc",6);
    *sample += *a;
    *sample += b;
    *sample += Person("wojtek", "cc", 6);
    assert( sample->get_length() == 3 );
}
void TestCustom::test_delete(){
    sample->wipeout(0);
    assert( sample->print_content(0).get_name() == "franek" );
}
void TestCustom::test_compare(){
    ClosedChain<Person> other;
    Person q("franek","k",5);
    Person w("wojtek", "cc",6);
    other += q;
    other += w;
    assert( *sample == other );
}
void TestCustom::test_inject(){
    Person pp("karol","ww",21);
    sample->inject(0, pp);
    assert( sample->print_content(0) == Person("karol","ww",21) );
}
void TestCustom::test_exceptions(){
    int i=0;
    try{
        sample->print_content(99);
    }
    catch (ExceededScope){
        i++;
    }
    try{
        sample->print_content(-5);
    }
    catch (IncorrectInput){
        i++;
    }
    assert( i == 2 );
}






