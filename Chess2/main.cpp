/// Chess.cpp
/// Made by Dallas Hart
/// Copyright 03/12/2019
/// This program allows the user to play chess with an AI (and Hopefully lose)

#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

#include "minimax.h"

void display (int board [8][8]);

int main()
{
    int masterBoard [8][8] = {
        {4,2,3,6,5,3,2,4},
        {1,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {-1,-1,-1,-1,-1,-1,-1,-1},
        {-4,-2,-3,-6,-5,-3,-2,-4}};

    /// start the program
    cout << "Welcome to chess!\n";
    cout << "Would you like to load a game or start a new one? (L - Load / S - Start)\n";

    /// load/save functionality
    while (true){
        string input;
        getline (cin, input);
        for (int i = 0; i < input.size(); i++){
            input[i]=toupper(input[i]);
            cout << input[i];
        }
        if (input == "LOAD" || input == "L"){ /// if user wants to load a pre saved game
            /// Load a file
            ifstream gameFile; /// file variable

            /// Loop until the file is open
            while(!gameFile.is_open()){
              /// ask for file path
              getline (cin, input); /// get file path

              gameFile.open(input);/// attempt to open file

              if (gameFile.is_open()){/// check if valid
               cout << "File Loaded Successfully!\n";
              }else{
                cout << "Incorrect File Path, Try Again.\n";
              }
            }
            /// load the board & ask if they want to play from this position
            for (int y = 0; y < 8; y++){
              getline(gameFile,input);
              for (int x = 0; x < 8; x++){
                masterBoard[y][x]=input[x];
              }
            }
            display(masterBoard);

            /// if so break, else wait for next move

        }else if (input == "START" || input == "S"){ /// if user wants to start a game
            /// start the game as normal
            display(masterBoard);
            break;
        }else{
            /// spit Error message
            cout << "Please enter any of the following valid inputs - Start, S, Load, L\n";
        }
    }

    /// Play the game

    /// take the players input
    /// Check for valid move
    /// output board

    /// AI
    /// minimax for the best move
    /// output board

    /// loop until computer or player resigns

    return 0;
}

void display(int board [8][8], bool view){
  
  
  
  for (int y = 0; y < 8; y++){
    for (int x = 0; x < 8; x++){
      string piece [8][8];
      if (board [y][x] < 0){
        piece [y][x] = "B";
      }else if (board [y][x] > 0){
        piece [y][x] = "W";
      }else{
        piece [y][x] = "__";
      }
      switch (abs(board[y][x])){
        case 6:
          piece [y][x].append("K");
          break;
        case 5:
          piece [y][x].append("Q");
          break;
        case 4:
          piece [y][x].append("R");
          break;
        case 3:
          piece [y][x].append("B");
          break;
        case 2:
          piece [y][x].append("N");
          break;
        case 1:
          piece [y][x].append("P");
          break;
      }
      cout << piece << " ";
    }
    cout << endl;
  }
}