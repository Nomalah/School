/// moves.cpp
/// Made by Dallas Hart
/// Copyright 03/12/2019
/// This program finds all the possible moves in a particular position & turn and oututs them in an array
#include <cmath>
#include <iostream>
using namespace std;

void kingMoves (int board [8][8], int &counter, int **foundMoves, int px, int py);
void pawnMoves (int board [8][8], int &counter, int **foundMoves, int px, int py, int pawnJump[3]);
void rookMoves (int board [8][8], int &counter, int **foundMoves, int px, int py);
void bishopMoves (int board [8][8], int &counter, int **foundMoves, int px, int py);
void knightMoves (int board [8][8], int &counter, int **foundMoves, int px, int py);

/// outputs all possible moves (the turn of)
int ** getMoves (bool turn, int board [8][8], bool castling[2], int pawnJump[3]){
    int **foundMoves = new int *[643];
    for (int i = 0; i< 643; i++){
        foundMoves [i]= new int [4]; /// the ABSOUTE MAXIMUM number of moves in a position
    }

    int counter = 0; /// counts
    /// Check for check? IDK how it will work (possibly minimax to stop check?)
    for (int y = 0; y<8; y++){
        for (int x = 0; x<8; x++){
            switch ((int)(abs(board [y][x]))){
                case 6:
                    /// find king moves
                    if ((-(board [y][x]/(int)(abs(board [y][x])))==1) == turn){
                        kingMoves (board, counter, foundMoves, x, y); /// uses counter (slighlty simplifies the organization)
                    }
                    break;
                case 1:
                    /// find pawn moves
                    if ((-(board [y][x]/(int)(abs(board [y][x])))==1) == turn){
                        pawnMoves (board, counter, foundMoves, x, y, pawnJump); /// also complicated (due to en passant & promotion)
                    }
                    break;
                case 2:
                    /// find knight moves
                    if ((-(board [y][x]/(int)(abs(board [y][x])))==1) == turn){
                        knightMoves (board, counter, foundMoves, x, y); /// VERY simple
                    }
                    break;
                case 4:
                    /// find rook moves
                    if ((-(board [y][x]/(int)(abs(board [y][x])))==1) == turn){
                        rookMoves (board, counter, foundMoves, x, y); /// VERY simple

                    }
                    break;
                case 3:
                    /// find bishop moves
                    if ((-(board [y][x]/(int)(abs(board [y][x])))==1) == turn){
                        bishopMoves (board, counter, foundMoves, x, y); /// diagonals are kinda complicated
                    }
                    break;
                case 5:
                    /// find queen moves
                    if ((-(board [y][x]/(int)(abs(board [y][x])))==1) == turn){
                        rookMoves (board, counter, foundMoves, x, y);
                        bishopMoves (board, counter, foundMoves, x, y);  /// basically rook+bishop
                    }
                    break;

            }
        }
    }

    foundMoves[0][0] = counter;
    return foundMoves;
}

void kingMoves (int board [8][8], int &counter, int **foundMoves, int px, int py){
    /// esally the most complicated search (i.e. has to search for check and castleling)

}

void pawnMoves (int board [8][8], int &counter, int **foundMoves, int px, int py, int pawnJump[3]){
    int tempX, tempY;
    if (board [py][px]>0){
        for (int i = -1; i <=1; i+=2){
            tempX = px+i;
            tempY = py+1;
            if (tempX<8 && tempX>=0){
                if (board [py][px]*board [tempY][tempX] < 0){
                    if (tempY == 7){
                        for (int p = 2; p<6; p++){
                            counter++;
                            foundMoves [counter][0] = 9;
                            foundMoves [counter][1] = p;
                            foundMoves [counter][2] = tempX;
                            foundMoves [counter][3] = tempY;
                        }
                    }else{
                        counter++;
                        foundMoves [counter][0] = px;
                        foundMoves [counter][1] = py;
                        foundMoves [counter][2] = tempX;
                        foundMoves [counter][3] = tempY;
                    }
                }
            }
        }
        tempY=py+1;
        if (board [tempY][px] == 0){
            if (tempY == 7){
                for (int p = 2; p<6; p++){
                    counter++;
                    foundMoves [counter][0] = 9;
                    foundMoves [counter][1] = p;
                    foundMoves [counter][2] = px;
                    foundMoves [counter][3] = tempY;
                }
            }else{
                counter++;
                foundMoves [counter][0] = px;
                foundMoves [counter][1] = py;
                foundMoves [counter][2] = px;
                foundMoves [counter][3] = tempY;
            }
            if (py == 1){
                /// jump
                if (board [3][px] == 0){
                    counter++;
                    foundMoves [counter][0] = px;
                    foundMoves [counter][1] = py;
                    foundMoves [counter][2] = px;
                    foundMoves [counter][3] = 3;
                }
            }
        }

        if (py == 4){
            /// en passent
        }
    }else{
        for (int i = -1; i <=1; i+=2){
            tempX = px+i;
            tempY = py-1;
            if (tempX<8 && tempX>=0){
                if (board [py][px]*board [tempY][tempX] < 0){
                    if (tempY == 7){
                        for (int p = 2; p<6; p++){
                            counter++;
                            foundMoves [counter][0] = 9;
                            foundMoves [counter][1] = -p;
                            foundMoves [counter][2] = tempX;
                            foundMoves [counter][3] = tempY;
                        }
                    }else{
                        counter++;
                        foundMoves [counter][0] = px;
                        foundMoves [counter][1] = py;
                        foundMoves [counter][2] = tempX;
                        foundMoves [counter][3] = tempY;
                    }
                }
            }
        }
        tempY=py-1;
        if (board [tempY][px] == 0){
            if (tempY == 7){
                for (int p = 2; p<6; p++){
                    counter++;
                    foundMoves [counter][0] = 9;
                    foundMoves [counter][1] = -p;
                    foundMoves [counter][2] = px;
                    foundMoves [counter][3] = tempY;
                }
            }else{
                counter++;
                foundMoves [counter][0] = px;
                foundMoves [counter][1] = py;
                foundMoves [counter][2] = px;
                foundMoves [counter][3] = tempY;
            }
            if (py == 6){
                /// jump
                if (board [4][px] == 0){
                    counter++;
                    foundMoves [counter][0] = px;
                    foundMoves [counter][1] = py;
                    foundMoves [counter][2] = px;
                    foundMoves [counter][3] = 4;
                }
            }
        }
        if (py == 3){
            /// en passent
        }
    }
}

void rookMoves (int board [8][8], int &counter, int **foundMoves, int px, int py){
    //cout << "here" << board [py][px] <<"  ";
    for (int d = 0; d<4; d++){/// Goes up and down (-1 & 1);
        int m = 1;
        int tempXY [2][4] = {{1,0,-1,0},{0,1,0,-1}};/// Directions in an array
        int tempX = px+tempXY [0][d]*m;
        int tempY = py+tempXY [1][d]*m;
        while (tempX < 8 && tempX >=0 && tempY < 8 && tempY >=0){/// make sure its within the bounds
            if (board [tempY][tempX] == 0){
                counter++;
                foundMoves [counter][0] = px;
                foundMoves [counter][1] = py;
                foundMoves [counter][2] = tempX;
                foundMoves [counter][3] = tempY;
            }else if (board [py][px]*board [tempY][tempX] < 0){
                counter++;
                foundMoves [counter][0] = px;
                foundMoves [counter][1] = py;
                foundMoves [counter][2] = tempX;
                foundMoves [counter][3] = tempY;
                break;
            }else{
                break;
            }
            m++;
            tempX = px+tempXY [0][d]*m;
            tempY = py+tempXY [1][d]*m;
        }
    }
}

void bishopMoves (int board [8][8], int &counter, int **foundMoves, int px, int py){
    for (int x = -1; x<2; x+=2){/// Goes left and right (-1 & 1);
        for (int y = -1; y<2; y+=2){/// Goes up and down (-1 & 1);
            int m = 1;
            int tempX = px+x*m;
            int tempY = py+y*m;
            while (tempX < 8 && tempX >=0 && tempY < 8 && tempY >=0){/// make sure its within the bounds
                if (board [tempY][tempX] == 0){
                    counter++;
                    foundMoves [counter][0] = px;
                    foundMoves [counter][1] = py;
                    foundMoves [counter][2] = tempX;
                    foundMoves [counter][3] = tempY;
                }else if (board [py][px]*board [tempY][tempX] < 0){
                    counter++;
                    foundMoves [counter][0] = px;
                    foundMoves [counter][1] = py;
                    foundMoves [counter][2] = tempX;
                    foundMoves [counter][3] = tempY;
                    break;
                }else{
                    break;
                }
                m++;
                tempX = px+x*m;
                tempY = py+y*m;
            }
        }
    }
}

void knightMoves (int board [8][8], int &counter, int **foundMoves, int px, int py){
    for (int d = 0; d<8; d++){/// Goes up and down (-1 & 1);
        int m = 1;
        int tempXY [2][8] = {{1,2,2,1,-1,-2,-2,-1},{2,1,-1,-2,-2,-1,1,2}};/// Directions in an array
        int tempX = px+tempXY [0][d];
        int tempY = py+tempXY [1][d];
        if (tempX < 8 && tempX >=0 && tempY < 8 && tempY >=0){/// make sure its within the bounds
            if (board [tempY][tempX] == 0){
                counter++;
                foundMoves [counter][0] = px;
                foundMoves [counter][1] = py;
                foundMoves [counter][2] = tempX;
                foundMoves [counter][3] = tempY;
            }else if (board [py][px]*board [tempY][tempX] < 0){
                counter++;
                foundMoves [counter][0] = px;
                foundMoves [counter][1] = py;
                foundMoves [counter][2] = tempX;
                foundMoves [counter][3] = tempY;
            }
        }
        m++;
    }
}
