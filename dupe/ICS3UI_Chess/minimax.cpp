/// minimax.cpp
/// Made by Dallas Hart
/// Copyright 03/12/2019
/// This program finds the best move in a given position

#include "eval.h"
#include "moves.h"

int bestMove (bool turn, int board [8][8], int moveHistory [], int depth, bool base){
    if (depth == 0){

    }
    /// get all the possible moves in the current position
    int *posMoves = getMoves(turn, board, moveHistory);

    for (int i = 1; i < posMoves[0]; i++){

    }
}
