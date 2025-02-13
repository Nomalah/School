/// assign_4_10_kTour.cpp
/// Dallas Hart
/// Copyright 1/3/2020
/// outputs a knights tour

#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

using namespace std;

bool tour (int board[8][8], int posX, int posY,int depth);
void tourThread (int posX, int posY);

int main()
{
    /// run with starting postiion
    tourThread(0, 0);
    return 0;
}

bool tour (int board[8][8], int posX, int posY, int depth)
{
    /// moves that knight
    int knightMoves [2][8] = {{1,2,2,1,-1,-2,-2,-1},{2,1,-1,-2,-2,-1,1,2}};

    /// if reach the ent the tour is succsessful
    if (depth == 64)
    {
        return true;
    }

    /// recusive loop ie try all moves around this position
    for (int i = 0; i<8; i++)
    {

        int curY = posY + knightMoves [1][i];
        int curX = posX + knightMoves [0][i];

        if (curX < 8 && curX >= 0 && curY < 8 && curY >= 0)
        {
            if (board[curY][curX] == -1)
            {
                board[curY][curX] = depth;
                if (tour(board,curX,curY,depth+1))
                {
                    return true;
                }
                board[curY][curX] = -1;
            }
        }
    }
    /// if all moves fail return false
    return false;
}

/// this function can be multithreaded (search multiple squares)
void tourThread (int posX, int posY)
{
    /// initialize board
    int board[8][8];
    for (int x = 0; x<8; x++)
    {
        for (int y = 0; y<8; y++)
        {
            board[y][x] = -1;
        }
    }
    board[posY][posX] = 0;

    /// run real function
    if (tour(board, posX, posY, 1))
    {
        /// open output
        ofstream output;
        output.open("output.txt");

        /// print to file
        for (int x = 0; x<8; x++)
        {
            for (int y = 0; y<8; y++)
            {
                output << board[y][x] << " ";
            }
            output << "\n";
        }
        ///close file
        output.close();
    }
}

/*
TEST CASES

Process returned 0 (0x0)   execution time : 0.821 s
Press any key to continue.

output.txt

0 37 58 35 42 47 56 51
59 34 1 48 57 50 43 46
38 31 36 41 2 45 52 55
33 60 39 26 49 54 3 44
30 9 32 61 40 25 22 53
17 62 27 10 23 20 13 4
8 29 18 15 6 11 24 21
63 16 7 28 19 14 5 12

*/
