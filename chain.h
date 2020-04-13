#ifndef CHAIN_H_INCLUDED
#define CHAIN_H_INCLUDED

#include <iostream>

class UniBox{/*
    Class for storing content. Each element contains pointer to the element - value.
    Contains also pointer to another element on list.
    Does not store position number on list.
*/
    int value;
    UniBox *anchor;     //stores pointer to next element

public:
    UniBox(const int);
    ~UniBox(){};//{ std::cout << "destruktor" << std::endl; };
    void set_anchor(UniBox*);

    int get_value() const;
    UniBox* get_anchor() const;
};


class ClosedChain{/*
    Chain Class managers our list. It contains of pointer to the first element.
    Number of elements is also stored.
*/
    unsigned lenght = 0;
    UniBox *alfa=nullptr;//, *omega=nullptr;

public:
    ClosedChain(){};
    ~ClosedChain();
    unsigned get_length() const { return lenght; };
    bool is_blanc();

    void append(UniBox* );
    UniBox* pick_predecessor(unsigned ) const;        //returns pointer to element element POINTING ON element given number
    UniBox* get_nth(unsigned ) const;
    void inject(unsigned, UniBox* );
    void wipeout(unsigned );
    bool operator==(const ClosedChain&) const;

    void operator+=(UniBox* );


};

std::ostream& operator<<(std::ostream& os, const ClosedChain& chain);
std::ostream& operator<<(std::ostream& os, const UniBox& content);



#endif // CHAIN_H_INCLUDED
