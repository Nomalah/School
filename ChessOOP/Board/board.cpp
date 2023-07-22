#include <cmath>
#include <iostream>

#include "../include.h"

board::board(int sizeX, int sizeY, int** pieces, bool turn, bool** castle)
{
    //ctor
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->turn = turn;
    this->castle = castle;

    data = new piece** [sizeX];
    for (int x = 0; x < this->sizeX; x++){
        data[x] = new piece* [sizeY];
        for (int y = 0; y < this->sizeY; y++){
            switch((int)std::abs(pieces[x][y])){
                case 6:
                    data[x][y] = new king((bool)((-pieces[x][y]/6+1)/2), x, y, this);
                    break;
                case 4:
                    data[x][y] = new rook((bool)((-pieces[x][y]/4+1)/2), x, y, this);
                    break;
                default:
                    data[x][y] = new vacant(false, x, y, this);
                    break;
            }
        }
    }
}

board::board(const board& other)
{
    //copy ctor
}

board& board::operator=(const board& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

void board::makeMove(action desiredMove){

}

action* board::legalMoves(){
    action* foundMoves = new action[100];
    foundMoves[0].length = 100;
    for (int x = 0; x < this->sizeX; x++){
        for (int y = 0; y < this->sizeY; y++){
            action* pieceMoves = (this->turn == val(x,y)->color) ?  val(x,y)->moves() : nullptr;
        }
    }
}

piece* board::val(int x, int y){
    return data[x][y];
}

void board::print(){
    std::cout << std::endl;
    for (int x = 0; x < this->sizeX; x++){
        for (int y = 0; y < this->sizeY; y++){
            std::cout << val(x,y)->name << " ";
        }
        std::cout << std::endl;
    }
}
