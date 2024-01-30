# Inputs:
#     board: 8 by 8 array of strings representing a chessboard state
# constraints:
#     each string in the board is one of 'K','Q','N','B','R','-':
#           'K' => King
#           'Q' => Queen
#           'N' => Knight
#           'B' => Bishop
#           'R' => Rook
#           '-' => Empty square
# Output: returns the number of moves that can be taken from this board state

def rook(board, row, col):
    moves = 0
    for i in range(row + 1, 8):
        if board[i][col] != "-":
            break
        moves += 1
            
    for i in range(row - 1, -1, -1):
        if board[i][col] != "-":
            break
        moves += 1
            
    for j in range(col + 1, 8):
        if board[row][j] != "-":
            break
        moves += 1
            
    for j in range(col - 1, -1, -1):
        if board[row][j] != "-":
            break
        moves += 1
    return moves


def bishop(board, row, col):
    moves = 0
    offset = 1
    while offset + col < 8 and offset + row < 8:
        if board[offset + row][offset + col] != "-":
            break
        moves += 1
        offset += 1
        
    offset = 1
    while col - offset > -1 and offset + row < 8:
        if board[offset + row][col - offset] != "-":
            break
        moves += 1
        offset += 1

    offset = 1
    while offset + col < 8 and row - offset > -1:
        if board[row - offset][offset + col] != "-":
            break
        moves += 1
        offset += 1

    offset = 1
    while col - offset > -1 and row - offset > -1:
        if board[row - offset][col - offset] != "-":
            break
        moves += 1
        offset += 1

    return moves

# Other things to note:
#       All the pieces follow the rules of movement that apply to a standard chess game
#       All the pieces are on the same team so do not worry about any other rules of chess 
#         beyond standard movement (no taking pieces, castling, checks, etc)
#       There may be multiples of any piece on the board, such as 7 Kings or 10 Knights
def countValidChessMoves( board ):
    moves = 0

    # King
    for row in range(8):
        for col in range(8):
            if board[row][col] == "K":
                for i in range(max(row - 1, 0), min(row + 1, 7) + 1):
                    for j in range(max(col - 1, 0), min(col + 1, 7) + 1):
                        if board[i][j] == "-":
                            moves += 1
            elif board[row][col] == "R":
                moves += rook(board, row, col)
            elif board[row][col] == "N":
                knight_offsets = [
                    [1, -2],
                    [2, -1],
                    [2, 1],
                    [1, 2],
                    [-1, 2],
                    [-2, 1],
                    [-2, -1],
                    [-1, -2]
                ]
                for offset in knight_offsets:
                    if 0 <= row + offset[0] <= 7 and 0 <= col + offset[1] <= 7:
                        if board[row + offset[0]][col + offset[1]] == "-":
                            moves += 1
            elif board[row][col] == "B":
                moves += bishop(board, row, col)
            elif board[row][col] == "Q":
                moves += rook(board, row, col)
                moves += bishop(board, row, col)

    return moves

# Testing code provided in main():
def main():
    # update this path with the path to your tests directory!
    testDir = "tests/"
    for i in range(1,9): #iterates over test files
        board=[]
        numMoves=0
        with open(f"{testDir}/board{i}.txt") as idFile:
            for idx, line in enumerate(idFile.readlines()):
                if idx == 8:
                    numMoves = int(line)
                    break
                row=[]
                for char in str(line).split()[0]:
                    row.append(char)
                board.append(row)
        print(board)
        calculatedMoves = countValidChessMoves(board)
        if numMoves == calculatedMoves:
            print("Passed")
        else:
            print(f"Failed, Expected: {numMoves}, Got: {calculatedMoves}")
    return 0

if __name__ == '__main__':
    main()