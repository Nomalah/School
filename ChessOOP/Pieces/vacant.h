#ifndef VACANT_H
#define VACANT_H

#include "../include.h"


class vacant : public piece
{
    public:
        vacant(bool color, int x, int y, board* linkedBoard);
        action* moves();
    protected:

    private:
};

#endif // VACANT_H
