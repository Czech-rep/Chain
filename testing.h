#ifndef TESTING_H_INCLUDED
#define TESTING_H_INCLUDED

#include "chain.h"


class TestChain{
    std::unique_ptr<ClosedChain<int>> sample = std::make_unique<ClosedChain<int>>();
public:
    TestChain();
    void execute();

    void test_fill_length();
    void test_delete();
    void test_empty();
    void test_compare();
    void test_inject();
    void test_exceptions();
};


class TestCustom{
    //tests ClosedChain against custom class: Person
public:
class Person{
    //implementation of private nested class Person
    std::string first_name, last_name;
    int number;
public:
    Person(std::string _first_name, std::string _last_name, int _number):
        first_name(_first_name), last_name(_last_name), number(_number) {}
    std::string get_name() const {     return first_name;    }
    bool operator==(const Person &other) const;
    bool operator!=(const Person &other) const;
};

private:
    std::unique_ptr<ClosedChain<Person>> sample = std::make_unique<ClosedChain<Person>>();
public:
    TestCustom();
    void execute();

    void test_fill_length();
    void test_delete();
    void test_empty();
    void test_compare();
    void test_inject();
    void test_exceptions();
};


/*
co musze zmienic
 sprawdz co robia metody dla pustej listy
*/




#endif // TESTING_H_INCLUDED
