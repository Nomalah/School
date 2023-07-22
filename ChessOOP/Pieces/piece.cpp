#include "../include.h"

piece::piece(bool color, int x, int y, board* linkedBoard)
{
    //ctor
    this->x = x;
    this->y = y;
    this->linkedBoard = linkedBoard;
}

piece::piece(const piece& other)
{
    //copy ctor
    this->color = other.color;
    this->x = other.x;
    this->y = other.y;
    this->linkedBoard = other.linkedBoard;
}

piece& piece::operator=(const piece& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    this->color = rhs.color;
    this->x = rhs.x;
    this->y = rhs.x;
    this->linkedBoard = rhs.linkedBoard;
    return *this;
}
