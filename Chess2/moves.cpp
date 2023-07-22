/// moves.cpp
/// Made by Dallas Hart
/// Copyright 03/12/2019
/// This program finds all the possible moves in a particular position & turn and oututs them in an array

void kingMoves (int board [8][8], int *counter, int *foundMoves);
void pawnMoves (int board [8][8], int *counter, int *foundMoves);
void rookMoves (int board [8][8], int *counter, int *foundMoves);
void queenMoves (int board [8][8], int *counter, int *foundMoves);
void bishopMoves (int board [8][8], int *counter, int *foundMoves);
void knightMoves (int board [8][8], int *counter, int *foundMoves);

/// outputs all possible moves (the turn of)
int * getMoves (bool turn, int board [8][8], int moveHistory [250]){
    int foundMoves [642]; /// the ABSOUTE MAXIMUM number of moves in a position

    int counter = 1; /// counts

    /// Check for check? IDK how it will work (possibly minimax to stop check?)

    /// find king moves
    kingMoves (board, &counter, foundMoves); /// uses counter (slighlty simplifies the organization)

    /// find pawn moves
    pawnMoves (board, &counter, foundMoves); /// also complicated (due to en passant & promotion)

    /// find knight moves
    knightMoves (board, &counter, foundMoves); /// VERY simple

    /// find rook moves
    rookMoves (board, &counter, foundMoves); /// VERY simple

    /// find bishop moves
    bishopMoves (board, &counter, foundMoves); /// diagonals are kinda complicated

    /// find queen moves
    queenMoves (board, &counter, foundMoves); /// basically rook+bishop
    return foundMoves;
}

void kingMoves (int board [8][8], int *counter, int *foundMoves){
    /// esally the most complicated search (i.e. has to search for check and castleling)
}

void pawnMoves (int board [8][8], int *counter, int *foundMoves){

}

void rookMoves (int board [8][8], int *counter, int *foundMoves){

}

void queenMoves (int board [8][8], int *counter, int *foundMoves){

}

void bishopMoves (int board [8][8], int *counter, int *foundMoves){

}

void knightMoves (int board [8][8], int *counter, int *foundMoves){

}
