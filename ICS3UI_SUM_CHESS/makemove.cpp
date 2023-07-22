#include <cmath>
#include <iostream>
using namespace std;

void makeMove (int disMove [4], int board [8][8], bool castling [2], int pawnJump[3]){
	switch (disMove [0]){ /// if move is a standard move (First digit is control and used)
			case 8:
                if (disMove [1] > 1){/// castling
                    int tempY = disMove[2]*7;
                    if (disMove [3] == 0){
                        board [tempY][4] = 0;
                        board [tempY][7] = 0;
                        board [tempY][5] = 4*(disMove[2]*-2+1);
                        board [tempY][6] = 6*(disMove[2]*-2+1);
                    }else{
                        board [tempY][0] = 0;
                        board [tempY][4] = 0;
                        board [tempY][3] = 4*(disMove[2]*-2+1);
                        board [tempY][2] = 6*(disMove[2]*-2+1);
                    }
                    castling[(int)(disMove[2]/abs(disMove[2])+1)/2] = false;
                }else{/// en passant
                    if (disMove [3] == 0){
                        board [disMove[3]][disMove[2]] = board [(disMove[3]-2)/-3*2+1+disMove[3]][disMove[2]+(disMove[1]*-2+1)];
                        board [(disMove[3]-2)/-3*2+1+disMove[3]][disMove[2]+(disMove[1]*-2+1)] = 0;
                    }
                }
			case 9:
                /// Promotion
                board [disMove[3]][disMove[2]] = disMove[1];
                board [(int)-(disMove[3]-(disMove[1]/abs(disMove[1])))][disMove[2]] = 0;
			default:
			    if (abs(board [disMove[1]][disMove[0]]) == 1){
                    if (abs(disMove[1]-disMove[3]==2)){
                        pawnJump [0] = 1;
                        pawnJump [1] = board [disMove[1]][disMove[0]];
                        pawnJump [2] = disMove[0];
                    }
			    }
                /// format = [StartX][StartY][GotoX][GotoY] (2d arrays have x & y switched)
                /// format = [StartX][StartY][GotoX][GotoY] (2d arrays have x & y switched)
                board [disMove[3]][disMove[2]] = board [disMove[1]][disMove[0]]; /// move the piece value to the other square
                board [disMove[1]][disMove[0]] = 0; /// always leaves a empty square behind
	}
}

void display(int board [8][8], bool view){
    for (int y = 0; y < 8; y++){
        for (int x = 0; x < 8; x++){
            string piece [8][8];
            int tempX = x;
            int tempY = y;
            if (view){
              	tempX=x*-1+7;
              	tempY=y*-1+7;
            }

            if (board [tempY][tempX] < 0){
              	piece [tempY][tempX] = "B";
            }else if (board [tempY][tempX] > 0){
              	piece [tempY][tempX] = "W";
            }else{
            	piece [tempY][tempX] = "__";
            }
            switch ((int)abs(board[tempY][tempX])){
              	case 6:
               		 piece [tempY][tempX].append("K");
               		 break;
          	  	case 5:
                    piece [tempY][tempX].append("Q");
                    break;
              	case 4:
                    piece [tempY][tempX].append("R");
                    break;
                case 3:
                    piece [tempY][tempX].append("B");
                    break;
              	case 2:
                    piece [tempY][tempX].append("N");
                    break;
              	case 1:
                    piece [tempY][tempX].append("P");
                    break;
            }
            cout << piece [tempY][tempX] << " ";
        }
        cout << y*-1+7;
        cout << endl;
    }
    for (int x = 0; x < 8; x++){
        cout << " " << x*-1+7 << " ";
    }
    cout << endl;
}
