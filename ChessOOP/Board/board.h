#ifndef BOARD_H
#define BOARD_H

#include "../include.h"

class board
{
    public:
        board(int sizeX = 0, int sizeY = 0, int** pieces = nullptr, bool turn = false, bool** castle = nullptr);
        board(const board& other);
        board& operator=(const board& other);

        void makeMove(action desiredMove);
        action* legalMoves();
        piece* val(int x, int y);

        void print();
    protected:

    private:
        int sizeX, sizeY;
        piece*** data;
        bool turn;
        bool** castle;
        /*
        turn; False = Whites Turn; True = Blacks Turn;
        castle; [0][0] = White Kingside; [0][1] = White Queenside; [1][0] = Black Kingside; [1][1] = Black Queenside
        */
};

#endif // BOARD_H
