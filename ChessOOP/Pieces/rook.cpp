#include "../include.h"

rook::rook(bool color, int x, int y, board* linkedBoard):piece(color, x, y, linkedBoard)
{
    //ctor
    if (color){
        name = "B";
    }else{
        name = "W";
    }
    name += "R";
}

action* rook::moves(){

}
