#include <iostream>

#include "include.h"

using namespace std;

int main()
{
    cout << "Welcome to Chess - OOP Version\n";
    cout << "Version 0.1a\n";
    int startingBoard[3][3] = {{0,4,6},{0,0,0},{-6,-4,0}};
    int** stBoard = new int*[3];
    for (int i = 0; i < 3; i++){
        stBoard[i] = new int [3];
        for (int j = 0; j < 3; j++){
            stBoard[i][j] = startingBoard[i][j];
        }
    }
    board masterBoard (3, 3, stBoard);
    masterBoard.print();
    return 0;
}
