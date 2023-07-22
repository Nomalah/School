#include "../include.h"

action::action(int length)
{
    //ctor
    this->length = length;
}

action::action(const action& other)
{
    //copy ctor
}

action& action::operator=(const action& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

action* action::operator+(action rhs){
    action* res = new action [(this->length+rhs.length)];
    for (uint64_t x = 0; x < this->length; x++){
        res[x] = *(this + x);
    }
    return res;
}
