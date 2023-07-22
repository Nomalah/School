#ifndef ACTION_H
#define ACTION_H

#include "../include.h"

class action
{
    public:
        int length;
        action(int length = 0);
        action(const action& other);
        action& operator=(const action& other);

        action* operator+(action rhs);
    protected:

    private:
};

#endif // ACTION_H
