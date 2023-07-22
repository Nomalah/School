#include "../include.h"

king::king(bool color, int x, int y, board* linkedBoard):piece(color, x, y, linkedBoard)
{
    //ctor
    if (color){
        name = "B";
    }else{
        name = "W";
    }
    name += "K";
}

action* king::moves(){

}
