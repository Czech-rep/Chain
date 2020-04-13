#include <iostream>
#include <string>

#include "chain.h"

UniBox::UniBox(const int input):
    value(input){}
int UniBox::get_value() const{
    return value;
}
void UniBox::set_anchor(UniBox* aim){
    anchor = aim;
}
UniBox* UniBox::get_anchor() const{
    return anchor;  //returns adress to next element //no, not we return object
}

bool ClosedChain::is_blanc(){
    if (alfa == nullptr)
        return true;
    return false;
}
void ClosedChain::append(UniBox* newby){        //newby - pointer to new elem. All operations on pointers
    if (alfa == nullptr){                     //so we begin list
        alfa = newby;
        newby->set_anchor(alfa);
    }
    else{
        UniBox* omega = get_nth(lenght-1);
        omega->set_anchor(newby);
        newby->set_anchor(alfa);
    }
    ++lenght;
}

UniBox* ClosedChain::pick_predecessor(unsigned point) const{
/*  gets pointer to object before object number "point"
    asked for the first returns the last element
    also asked for the place after last element (length) will return the last
*/
    if (point > lenght){
            std::string err = "demanded index out of list ";
        throw err;
    }
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
UniBox* ClosedChain::get_nth(unsigned n) const{
    if (n==0)
        return alfa;
    return pick_predecessor(n)->get_anchor();
}
void ClosedChain::inject(unsigned point, UniBox* newby){
    UniBox* pointing = pick_predecessor(point);
    if (pointing == nullptr){
        throw "finding predecessor not succeded ";                             //how to step out program
    }
    newby->set_anchor(pointing->get_anchor());
    pointing->set_anchor(newby);
    lenght += 1;
    if (point == 0)
        alfa = newby;
}
void ClosedChain::wipeout(unsigned n){
    UniBox* pointing = pick_predecessor(n);
    UniBox* passing = pointing->get_anchor();
    pointing->set_anchor(passing->get_anchor());
    --lenght;
    passing -> ~UniBox();
    if (n == 0)
        alfa = get_nth(1);
}
bool ClosedChain::operator==(const ClosedChain& other) const{
    if (lenght != other.get_length())
        return false;
    if (lenght == 0)
        return true;
    UniBox *shifting = alfa;
    UniBox *shifting_other = other.get_nth(0);
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
void ClosedChain::operator+=(UniBox* newby){
    append(newby);
}
ClosedChain::~ClosedChain(){
    unsigned iter=0;
    UniBox *next, *shifting = alfa;
    while (iter < lenght){
        next = shifting->get_anchor();
        delete shifting;
        shifting = next;
        ++iter;
    }
}


std::ostream& operator<<(std::ostream& os, const ClosedChain& chain){
    if (chain.get_nth(0) == nullptr)
        return os << "list is empty " << std::endl;
    std::string content = "";
    UniBox *shifting, *first;
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
std::ostream& operator<<(std::ostream& os, const UniBox& content){
     os << content.get_value();
     return os;
}












