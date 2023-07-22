#ifndef PIECE_H
#define PIECE_H

#include <string>

#include "../include.h"

class piece
{
    public:
        /// color False = white true = false
        bool color;
        int x, y;
        std::string name = "bp";
        board* linkedBoard;

        piece(bool color, int x, int y, board* linkedBoard);
        piece(const piece& other);
        piece& operator=(const piece& other);

        //template <class T>
        virtual action* moves() = 0;


    protected:
    private:
};

#endif // PIECE_H
