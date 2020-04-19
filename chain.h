#ifndef CHAIN_H_INCLUDED
#define CHAIN_H_INCLUDED

#include <iostream>
#include <memory>


template<typename T>
class ClosedChain{/*
    Chain Class managers our list. It contains of pointer to the first element.
    Number of elements is also stored.
*/
public:
    class UniBox{/*
        Class for storing content. Each element contains pointer to the element - value.
        Contains also pointer to another element on list.
        Does not store position number on list.
    */
        T value;                // stores content - will be provided
        UniBox *anchor;         // stores pointer to next element - next UniBox
    public:
        UniBox(const T );
        //~UniBox(){      delete value;    };//{ std::cout << "destruktor" << std::endl; };       // a co jesli value jest statyczne ?????
        void set_anchor(UniBox*);

        T get_value() const;
        UniBox* get_anchor() const;
    };


private:
    unsigned lenght = 0;
    ClosedChain<T>::UniBox *alfa=nullptr;
    //std::shared_ptr<UniBox> alfa = std::make_shared<UniBox>();


public:
    ClosedChain(){};
    ~ClosedChain();

    unsigned get_length() const { return lenght; };
    bool is_blanc();

    void append(T );
    void operator+=(T );
    UniBox* pick_predecessor(int ) const;
    UniBox* get_nth(int ) const;
    void inject(int, T );
    void wipeout(int );

    bool operator==(const ClosedChain&) const;


    class Error{
    public:
        //Error(){};
        void print_message(){ std::cout << "Chain error message: "; }
    };

    class IncorrectInput: public Error{
        int n;
    public:
        IncorrectInput(int _n): n(_n){ Error::print_message(); };
        void print_message(){
            std::cout << "not allowed negative index: " << n << std::endl;
        }
    };

    class ExceededScope: public Error{
        unsigned len, n;
    public:
        ExceededScope(){};
        ExceededScope(unsigned _n, unsigned _len): n(_n), len(_len){};
        void print_message(){
            Error::print_message();
            std::cout << n << " not in range of list length " << len << " " << std::endl;
        }
    };

};

// =========================== IMPLEMENTATION =========================== \\



template<typename T>
ClosedChain<T>::UniBox::UniBox(const T input):
    value(input){}

template<typename T>
T ClosedChain<T>::UniBox::get_value() const{
    return value;
}
template<typename T>
void ClosedChain<T>::UniBox::set_anchor(UniBox* aim){
    anchor = aim;
}
template<typename T>
typename ClosedChain<T>::UniBox* ClosedChain<T>::UniBox::get_anchor() const{
    return anchor;
}

template<typename T>
bool ClosedChain<T>::is_blanc(){
    if (alfa == nullptr)
        return true;
    return false;
}
template<typename T>
void ClosedChain<T>::append(T _newby){
    UniBox* newby = new ClosedChain<T>::UniBox(_newby);                 //pytanie - co to tak na prawde obiekt newby - ile żyje?
    if (alfa == nullptr){                                   //so we begin list
        alfa = newby;
        newby->set_anchor(alfa);
    }
    else{
        UniBox* omega = pick_predecessor(0);
        omega->set_anchor(newby);
        newby->set_anchor(alfa);
    }
    ++lenght;
}

template<typename T>
typename ClosedChain<T>::UniBox* ClosedChain<T>::pick_predecessor(int point) const{
/*  gets pointer to object before object number "point"
    asked for the first returns the last element
    also asked for the place after last element (length) will return the last
*/
    if (point < 0)
        throw IncorrectInput(point);
    if (point > lenght)
        throw ExceededScope(point, lenght);

    UniBox* floating_pointer = alfa;
    unsigned i=0;
    while (i+1 < lenght){
        if ( i+1 == point )
            break;
        floating_pointer = floating_pointer->get_anchor();
        ++i;
    }
    return floating_pointer;
}
template<typename T>
typename ClosedChain<T>::UniBox* ClosedChain<T>::get_nth(int n) const{
    if (n < 0)
        throw IncorrectInput(n);
    if (n==0)
        return alfa;
    return pick_predecessor(n)->get_anchor();
}
template<typename T>
void ClosedChain<T>::inject(int point, T _newby){
    UniBox* pointing = pick_predecessor(point);
    if (pointing == nullptr){
        throw "finding predecessor not succeded ";
    }
    UniBox* newby = new ClosedChain<T>::UniBox(_newby);
    newby->set_anchor(pointing->get_anchor());
    pointing->set_anchor(newby);
    lenght += 1;
    if (point == 0)
        alfa = newby;
}
template<typename T>
void ClosedChain<T>::wipeout(int n){
    UniBox* pointing = pick_predecessor(n);
    UniBox* passing = pointing->get_anchor();
    if (n == 0)
        alfa = get_nth(1);
    pointing->set_anchor(passing->get_anchor());
    --lenght;
    delete passing;
}
template<typename T>
bool ClosedChain<T>::operator==(const ClosedChain<T>& other) const{
    if (lenght != other.get_length())
        return false;
    if (lenght == 0)                                //teraz wiem ze dlugosci sa rowne
        return true;
    UniBox *shifting = alfa;
    UniBox *shifting_other = other.get_nth(0);
    while (true){
        if (shifting == alfa)                       //a wiec przeszedl caly lancuch
            break;
        if (shifting->get_value() != shifting_other->get_value())
            return false;
        shifting = shifting->get_anchor();
        shifting_other = shifting_other->get_anchor();
    }
    return true;
}
template<typename T>
void ClosedChain<T>::operator+=(T _newby){
    append(_newby);
}
template<typename T>
ClosedChain<T>::~ClosedChain(){
    unsigned iter=0;
    UniBox *next, *shifting = alfa;
    while (iter < lenght){
        next = shifting->get_anchor();
        delete shifting;                //iteruje po wszystkich boxach i delete. to jest ok bo UniBox zawsze jest tworzony z NEW
        shifting = next;
        ++iter;
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const typename ClosedChain<T>::UniBox& content){
    std::cout<<"check "<<std::endl;
     os << content->get_value();
     return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const ClosedChain<T>& chain){
    if (chain.get_nth(0) == nullptr)
        return os << "list is empty " << std::endl;
    typename ClosedChain<T>::UniBox *shifting, *first;
    shifting = first = chain.get_nth(0);
    //os << shifting->get_value();                                //===============zle, uzyj operatora
    os << shifting->get_value();
    while (true){
        shifting = shifting->get_anchor();
        if (shifting == first)
            break;
        os << ", " << shifting->get_value();
    }
    os << "; " << std::endl;
    return os;
}




#endif // CHAIN_H_INCLUDED
