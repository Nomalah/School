/// eval.cpp
/// Made by Dallas Hart
/// Copyright 03/12/2019
/// This program evaluates the current position
#include <cmath>
#include <iostream>
using namespace std;
/// evaluation function
int evalBoard (int board [8][8]){
    ///piece square tables
    int pawnSquare[8][8] =
    {{0,  0,  0,  0,  0,  0,  0,  0},
    {50, 50, 50, 50, 50, 50, 50, 50},
    {10, 10, 20, 30, 30, 20, 10, 10},
    {5,  5, 10, 25, 25, 10,  5,  5},
    {0,  0,  0, 20, 20,  0,  0,  0},
    {5, -5,-10,  0,  0,-10, -5,  5},
    {5, 10, 10,-20,-20, 10, 10,  5},
    {0,  0,  0,  0,  0,  0,  0,  0}};
    /// Neural network??
    /// or basic evaluation i.e. Your piece value & position - Opponent's piece value & position
    int total = 0;
    for (int y = 0; y<8; y++){
        for (int x = 0; x<8; x++){
            int color = (abs (board[y][x]))/board[y][x];
            switch (board[y][x]){
                case 1:
                    total += 10*color;
                    if (color == -1){
                        total -= pawnSquare[y][x];
                    }else{
                        total += pawnSquare[7-y][x];
                    }
                    break;
                case 2:
                    total += 30*color;
                    break;
                case 3:
                    total += 30*color;
                    break;
                case 4:
                    total += 50*color;
                    break;
                case 5:
                    total += 90*color;
                    break;
                case 6:
                    total += 1000*color;
                    break;

            }
        }
    }
    return total;
}


