/// Chess.cpp
/// Made by Dallas Hart
/// Copyright 03/12/2019
/// This program allows the user to play chess with an AI (and Hopefully lose)

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

#include "minimax.h"
#include "moves.h"
#include "makemove.h"

int *playerMove (int board [8][8]);
void printMove (int disMove[4], int board [8][8]);

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
    bool masterTurn = false; /// false = whites move, true = blacks
    bool castling [2] = {true, true}; /// 0 = black 1 = white & TRUE = NO CASTLE YET
    int enPassant [3] = {0, 0, 0}; /// 0 = enable, 1 = color, 2 = coloumn
    bool gameOver = false;
    /// start the program
    cout << "Welcome to chess!\n";
    cout << "Would you like to load a game or start a new one? (L - Load / S - Start)\n";

    /// load/save functionality
    while (true){
        string input;
        getline (cin, input);
        for (uint32_t i = 0; i < input.size(); i++){
            input[i]=toupper(input[i]);
        }
        if (input == "LOAD" || input == "L"){ /// if user wants to load a pre saved game
            /// Load a file
            ifstream gameFile; /// file variable

            /// Loop until the file is open
            while(!gameFile.is_open()){
                /// ask for file path
                string filePath;
                getline (cin, filePath); /// get file path

                gameFile.open(filePath.c_str());/// attempt to open file

                if (gameFile.is_open()){/// check if valid
                    cout << "File Loaded Successfully!\n";
                }else{
                    cout << "Incorrect File Path, Try Again.\n";
                }
            }
            /// load the board & ask if they want to play from this position
            int intInput;
            for (int y = 0; y < 8; y++){
              	for (int x = 0; x < 8; x++){
					gameFile >> intInput;
                    masterBoard[y][x]= intInput;
              	}
            }
            /// display the board
            display(masterBoard, false);

            /// get the players turn in the current position
            gameFile >> masterTurn;

            /// get the next turn/ask if they want to play
            while (!gameFile.eof()){
                bool exit = false;
                gameFile >> input;/// get the turn
                int tempMove [4];
                for (int i = 0; i < 4; i++){
                    tempMove [i] = input [i];
                }
                makeMove (tempMove, masterBoard, castling, enPassant);
                display(masterBoard, false);
                masterTurn = !masterTurn;
                /// move
                while (true){
                    cout << "Do you want to play from this position? (Y/N)\n";
                    cin >> input;
                    input[0] = toupper(input[0]);
                    if (input[0] == 'Y'){
                        exit = true;
                    }else if (input[0] == 'N'){
                        break;
                    }else{
                        cout << "You did not enter a valid input! (Y/N)\n";
                    }
                }
                if (exit){
                    gameFile.close();
                    break;
                }
            }
            /// if so break, else wait for next move
            break;
        }else if (input == "START" || input == "S"){ /// if user wants to start a game
            /// start the game as normal
            cout << "Starting Game...\n";
            break;
        }else{
            /// spit Error message
            cout << "Please enter any of the following valid inputs - Start, S, Load, L\n";
        }
    }

    while(true){
        /// Play the game
        display(masterBoard, 1);

        /// take the players input
        int **legalMoves = getMoves(masterTurn, masterBoard, castling, enPassant);
        int *desiredMove;
        while (true){
            desiredMove = playerMove(masterBoard);
            if (desiredMove [0] == 9 && desiredMove [1] == 9 && desiredMove [2] == 9 && desiredMove [3] == 9){
                cout << "THE PLAYER RESIGNS!\n";
                gameOver=true;
                break;
            }
            /// Check for valid move
            bool legalMove = false;
            for (int i = 1; i <= legalMoves[0][0]; i++){
                if (legalMoves[i][0] == desiredMove[0] && legalMoves[i][1] == desiredMove[1] && legalMoves[i][2] == desiredMove[2] && legalMoves[i][3] == desiredMove[3]){
                    legalMove = true;
                }
            }
            if (legalMove){
                break;
            }
        }
        if (gameOver){
            break;
        }
        printMove(desiredMove,masterBoard);
        makeMove (desiredMove, masterBoard, castling, enPassant);
        masterTurn=!masterTurn;
        /// output board
        display(masterBoard, 1);

        /// AI
        /// minimax for the best move
        int *aiMove = new int [4];
        aiMove = bestMove(masterTurn, masterBoard, castling, enPassant, 3, true);
        printMove(aiMove,masterBoard);
        if (aiMove [0] == 9 && aiMove [1] == 9 && aiMove [2] == 9 && aiMove [3] == 9){
            cout << "The Computer Resigns!";
            break;
        }
        makeMove (aiMove, masterBoard, castling, enPassant);
        masterTurn=!masterTurn;
        /// loop until computer or player resigns
    }
    return 0;
}

void printMove (int disMove[4], int board [8][8]){
    switch ((int)abs(board[disMove[1]][disMove[0]])){
        case 6:
            cout << "K";
            break;
        case 5:
            cout << "Q";
            break;
        case 4:
            cout << "R";
            break;
        case 3:
            cout << "B";
            break;
        case 2:
            cout << "N";
            break;
        case 1:
            cout << "P";
            break;
    }
    char moveLetter = disMove[0]+97;
    cout << moveLetter << disMove[1];
    moveLetter = disMove[2]+97;
    cout << moveLetter << disMove[3]<<endl;
    cout << board[disMove[1]][disMove[0]] << endl;
}

int * playerMove(int board [8][8]){
    int * output = new int [4];
    string input;
    while (true){
        bool outFlag = true;
        cout << "What move do you want to make? (Start X, Start Y, End X, End Y)\n";
        cin >> input;
        for (int i = 0; i < 4; i++){
            output[i] = input[i] - 48;
            if (output [i]>9||output [i]<0){
                outFlag = false;
                break;
            }
        }
        if (outFlag){
            break;
        }else{
            cout << "You did not enter a valid input! " << output[0] << "\n";
        }
    }
    return output;
}
