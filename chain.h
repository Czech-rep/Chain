#ifndef CHAIN_H_INCLUDED
#define CHAIN_H_INCLUDED

#include <iostream>
#include <memory>
template<typename T> class ClosedChain;
template<typename T> std::ostream& operator<<(std::ostream& os, const ClosedChain<T>& chain);

template<typename T>
class ClosedChain{/*
    Chain Class managers our list. It contains of pointer to the first element.
    Number of elements is also stored.
*/
private:
    class Node{/*
        Class for storing content. Each element contains pointer to the element - value.
        Contains also pointer to another element on list.
        Does not store position number on list.
    */
        T value;                // stores content - will be provided
        Node *anchor;         // stores pointer to next element - next Node
    public:
        Node(const T );
        Node(Node&){std::cout << "copied" << std::endl; }
        void set_anchor(Node*);

        T get_value() const;
        Node* get_anchor() const;
        friend std::ostream& operator<<(std::ostream& os, const Node& content){       //works only as inline function
             os << content.get_value();
             return os;
        }
    };

private:
    int lenght = 0;
    ClosedChain<T>::Node *alfa=nullptr;

    Node* pick_predecessor(int ) const;
    Node* get_nth(int ) const;

public:
    ClosedChain(){};
    ~ClosedChain();

    unsigned get_length() const { return lenght; };
    bool is_blanc();

    void append(T );
    void operator +=(T );
    T get_content(int ) const;
    void inject(int, T );
    void wipeout(int );
    bool operator==(const ClosedChain&) const;

    friend std::ostream& operator<< <>(std::ostream& os, const ClosedChain<T>& chain);
};

class Error{
public:
    void print_message(){ std::cout << "Chain error message: "; }   //problem jest z wyswietlaniem tego bez przyczyny
};
class IncorrectInput: public Error{
    int n;
public:
    IncorrectInput(int _n): n(_n){};
    void print_message(){
        Error::print_message();
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


// =========================== IMPLEMENTATION ===========================



template<typename T>
ClosedChain<T>::Node::Node(const T input):
    value(input){}

template<typename T>
T ClosedChain<T>::Node::get_value() const{
    return value;
}
template<typename T>
void ClosedChain<T>::Node::set_anchor(Node* aim){
    anchor = aim;
}
template<typename T>
typename ClosedChain<T>::Node* ClosedChain<T>::Node::get_anchor() const{
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
    Node* newby = new ClosedChain<T>::Node(_newby);                 //pytanie - co to tak na prawde obiekt newby - ile żyje?
    //std::unique_ptr<Node> newby = std::make_unique<Node>(_newby);
    if (alfa == nullptr){
        alfa = newby;
        newby->set_anchor(alfa);
    }
    else{
        Node* omega = pick_predecessor(0);
        omega->set_anchor(newby);
        newby->set_anchor(alfa);
    }
    ++lenght;
}

template<typename T>
typename ClosedChain<T>::Node* ClosedChain<T>::pick_predecessor(int point) const{
/*  gets pointer to object before object number "point"
    asked for the first returns the last element
    also asked for the place after last element (length) will return the last
*/
    if (point < 0)
        throw IncorrectInput(point);
    if (point >= lenght)
        throw ExceededScope(point, lenght);

    Node* floating_pointer = alfa;
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
typename ClosedChain<T>::Node* ClosedChain<T>::get_nth(int n) const{
    if (n < 0)
        throw IncorrectInput(n);
    if (n==0)
        return alfa;
    return pick_predecessor(n)->get_anchor();
}
template<typename T>
void ClosedChain<T>::inject(int point, T _newby){
    Node* pointing = pick_predecessor(point);
    if (pointing == nullptr){
        throw "finding predecessor not succeded ";
    }
    Node* newby = new ClosedChain<T>::Node(_newby);
    newby->set_anchor(pointing->get_anchor());
    pointing->set_anchor(newby);
    lenght += 1;
    if (point == 0)
        alfa = newby;
}
template<typename T>
void ClosedChain<T>::wipeout(int n){
    Node* pointing = pick_predecessor(n);
    Node* standing = pointing->get_anchor();
    pointing->set_anchor(standing->get_anchor());
    delete standing;
    --lenght;
    if (n == 0){
        if (lenght == 0){
            alfa = nullptr;
        }
        else{
            alfa = pointing->get_anchor();
        }
    }
}
template<typename T>
bool ClosedChain<T>::operator==(const ClosedChain<T>& other) const{
    if (lenght != other.get_length())
        return false;
    if (lenght == 0)                                //teraz wiem ze dlugosci sa rowne
        return true;
    Node *shifting = alfa;
    Node *shifting_other = other.get_nth(0);
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
    Node *next, *shifting = alfa;
    while (iter < lenght){
        next = shifting->get_anchor();
        delete shifting;
        shifting = next;
        ++iter;
    }
}
template<typename T>
T ClosedChain<T>::get_content(int n) const{
    return get_nth(n)->get_value();
}

template<typename T>
std::ostream& operator<< (std::ostream& os, const ClosedChain<T>& chain){
    if (chain.alfa == nullptr)
        return os << "list is empty " << std::endl;
    unsigned n = 1;
    typename ClosedChain<T>::Node *shifting = chain.alfa, *head = chain.alfa;
    os << *shifting;                        //tutaj korzystam z przeladowanego operatora wypisywania dla Node
    while( true ){
        shifting = shifting->get_anchor();
        if (shifting == head)
            break;
        os << ", " << *shifting;
    }
    os << "; " << std::endl;
    return os;
}


#endif // CHAIN_H_INCLUDED
