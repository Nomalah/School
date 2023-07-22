#ifndef KING_H
#define KING_H

#include "../include.h"

class king : public piece
{
    public:
        king(bool color, int x, int y, board* linkedBoard);
        //template <class T>
        action* moves();
    protected:

    private:
};

#endif // KING_H
