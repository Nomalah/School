/// minimax.cpp
/// Made by Dallas Hart
/// Copyright 03/12/2019
/// This program finds the best move in a given position
#include <iostream>
#include "eval.h"
#include "moves.h"
#include "makemove.h"
#include "minimax.h"

using namespace std;

int * bestMove (bool turn, int board [8][8], bool castling[2] , int pawnJump[3], int depth, bool base){
    if (depth == 0){
        int *positionEval = new int [1];
        positionEval[0] = evalBoard(board);
        return positionEval;
    }else if (base){
        int **posMoves = getMoves(turn, board, castling, pawnJump);
        int *bestFoundMove = new int [4];
        for (int i = 0; i <4 ;i++) bestFoundMove[i]=9;
        int *bestVal = new int [1];
        bestVal[0] = -99999*(turn*-2+1);
        for (int i = 1; i <= posMoves[0][0]; i++){
            //for (int x = 0; x<4; x++) cout << posMoves [i][x];
            int localBoard [8][8];
            for (int y = 0; y < 8; y++){
                for (int x = 0; x < 8; x++){
                    localBoard [y][x] = board[y][x];
                }
            }
            bool *localCastling = castling;
            int *localPawnJump = pawnJump;
            makeMove(posMoves[i], localBoard, localCastling, localPawnJump);
            int *tempBestVal = new int [1];
            tempBestVal = bestMove(!turn, localBoard, castling, pawnJump, depth-1, false);
            if (turn) {
                if (bestVal[0]>tempBestVal[0]){
                    bestVal[0] = tempBestVal[0];
                    for (int x = 0; x<4; x++) bestFoundMove [x] = posMoves[i][x];
                }
            }else{
                if (bestVal[0]<tempBestVal[0]){
                    bestVal[0] = tempBestVal[0];
                    for (int x = 0; x<4; x++) bestFoundMove [x] = posMoves[i][x];
                }
            }
            //for (int x = 0; x<4; x++) cout << bestFoundMove [x];
            //cout << endl;
        }
        return bestFoundMove;
    }else{
        /// get all the possible moves in the current position
        int **posMoves = getMoves(turn, board, castling, pawnJump);
        int *bestVal = new int [1];
        bestVal[0] = -99999*(turn*-2+1);
        for (int i = 1; i <=posMoves[0][0]; i++){
            int localBoard [8][8];
            for (int y = 0; y < 8; y++){
                for (int x = 0; x < 8; x++){
                    localBoard [y][x] = board[y][x];
                }
            }
            bool *localCastling = castling;
            int *localPawnJump = pawnJump;
            makeMove(posMoves[i], localBoard, localCastling, localPawnJump);
            int *tempBestVal = bestMove(!turn, localBoard, castling, pawnJump, depth-1, false);
            if (turn) {
                if (bestVal[0] >tempBestVal[0]){
                    bestVal[0] = tempBestVal[0];
                }
            }else{
                if (bestVal[0] <tempBestVal[0]){
                    bestVal[0] = tempBestVal[0];
                }
            }
        }
        return bestVal;
    }
}
