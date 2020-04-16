#ifndef CHAIN_H_INCLUDED
#define CHAIN_H_INCLUDED

#include <iostream>

template<typename T>
class UniBox{/*
    Class for storing content. Each element contains pointer to the element - value.
    Contains also pointer to another element on list.
    Does not store position number on list.
*/
    T value;
    UniBox *anchor;     //stores pointer to next element

public:
    UniBox(T);
    ~UniBox(){};//{ std::cout << "destruktor" << std::endl; };
    void set_anchor(UniBox*);

    T get_value() const;
    UniBox* get_anchor() const;
};


template<typename T>
class ClosedChain{/*
    Chain Class managers our list. It contains of pointer to the first element.
    Number of elements is also stored.
*/
    unsigned lenght = 0;
    UniBox<T> *alfa=nullptr;//, *omega=nullptr;

public:
    ClosedChain(){};
    ~ClosedChain();
    unsigned get_length() const { return lenght; };
    bool is_blanc();

    void append(UniBox<T>* );
    UniBox<T>* pick_predecessor(unsigned ) const;        //returns pointer to element element POINTING ON element given number
    UniBox<T>* get_nth(unsigned ) const;
    void inject(unsigned, UniBox<T>* );
    void wipeout(unsigned );
    bool operator==(const ClosedChain&) const;

    void operator+=(UniBox<T>* );


};
/*
std::ostream& operator<<(std::ostream& os, const ClosedChain& chain);
std::ostream& operator<<(std::ostream& os, const UniBox& content);
*/

// =========================== IMPLEMENTATION =========================== \\

template<typename T>
UniBox<T>::UniBox(T input):
    value(input){}

template<typename T>
T UniBox<T>::get_value() const{
    return value;
}
template<typename T>
void UniBox<T>::set_anchor(UniBox* aim){
    anchor = aim;
}
template<typename T>
UniBox<T>* UniBox<T>::get_anchor() const{
    return anchor;  //returns adress to next element //no, not we return object
}

template<typename T>
bool ClosedChain<T>::is_blanc(){
    if (alfa == nullptr)
        return true;
    return false;
}
template<typename T>
void ClosedChain<T>::append(UniBox<T>* newby){        //newby - pointer to new elem. All operations on pointers
    if (alfa == nullptr){                     //so we begin list
        alfa = newby;
        newby->set_anchor(alfa);
    }
    else{
        UniBox<T>* omega = get_nth(lenght-1);
        omega->set_anchor(newby);
        newby->set_anchor(alfa);
    }
    ++lenght;
}

template<typename T>
UniBox<T>* ClosedChain<T>::pick_predecessor(unsigned point) const{
/*  gets pointer to object before object number "point"
    asked for the first returns the last element
    also asked for the place after last element (length) will return the last
*/
    if (point > lenght){
            std::string err = "demanded index out of list ";
        throw err;
    }
    UniBox<T>* floating_pointer = alfa;
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
UniBox<T>* ClosedChain<T>::get_nth(unsigned n) const{
    if (n==0)
        return alfa;
    return pick_predecessor(n)->get_anchor();
}
template<typename T>
void ClosedChain<T>::inject(unsigned point, UniBox<T>* newby){
    UniBox<T>* pointing = pick_predecessor(point);
    if (pointing == nullptr){
        throw "finding predecessor not succeded ";                             //how to step out program
    }
    newby->set_anchor(pointing->get_anchor());
    pointing->set_anchor(newby);
    lenght += 1;
    if (point == 0)
        alfa = newby;
}
template<typename T>
void ClosedChain<T>::wipeout(unsigned n){
    UniBox<T>* pointing = pick_predecessor(n);
    UniBox<T>* passing = pointing->get_anchor();
    pointing->set_anchor(passing->get_anchor());
    --lenght;
    passing -> ~UniBox();
    if (n == 0)
        alfa = get_nth(1);
}
template<typename T>
bool ClosedChain<T>::operator==(const ClosedChain<T>& other) const{
    if (lenght != other.get_length())
        return false;
    if (lenght == 0)
        return true;
    UniBox<T> *shifting = alfa;
    UniBox<T> *shifting_other = other.get_nth(0);
    while (true){
        if (shifting == alfa)
            break;
        if (shifting->get_value() != shifting_other->get_value())
            return false;
        shifting = shifting->get_anchor();
        shifting_other = shifting_other->get_anchor();
    }
    return true;
}
template<typename T>
void ClosedChain<T>::operator+=(UniBox<T>* newby){
    append(newby);
}
template<typename T>
ClosedChain<T>::~ClosedChain(){
    unsigned iter=0;
    UniBox<T> *next, *shifting = alfa;
    while (iter < lenght){
        next = shifting->get_anchor();
        delete shifting;
        shifting = next;
        ++iter;
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const ClosedChain<T>& chain){
    if (chain.get_nth(0) == nullptr)
        return os << "list is empty " << std::endl;
    std::string content = "";
    UniBox<T> *shifting, *first;
    shifting = first = chain.get_nth(0);
    os << *shifting;
    while (true){
        shifting = shifting->get_anchor();
        if (shifting == first)
            break;
        os << ", " << *shifting;
    }
    os << "; " << std::endl;
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const UniBox<T>& content){
     os << content.get_value();
     return os;
}

//instantyzacja
        template class UniBox<int>;
        template class ClosedChain<int>;



#endif // CHAIN_H_INCLUDED
