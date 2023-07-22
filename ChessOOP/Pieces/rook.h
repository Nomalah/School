#ifndef ROOK_H
#define ROOK_H

#include "../include.h"


class rook : public piece
{
    public:
        rook(bool color, int x, int y, board* linkedBoard);
        action* moves();
    protected:

    private:
};

#endif // ROOK_H
