#include "../include.h"

vacant::vacant(bool color, int x, int y, board* linkedBoard):piece(color, x, y, linkedBoard)
{
    //ctor
    name = "__";
}

action* vacant::moves(){
    return nullptr;
}
