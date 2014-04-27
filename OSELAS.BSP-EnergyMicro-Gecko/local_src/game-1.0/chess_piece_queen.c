// Kontrollert av eirik flogard



#include "chess_board.h"
#include "chess_piece.h"



//ChessPieceQueen

bool validMoveQueen(ChessBoard* board,ChessPiece* pieces, Cell to)
{
    return (validMoveStraight(board, pieces, to) ||
            validMoveDiagonal(board, pieces, to));
}

Cell* getPossibleMovesQueen(ChessBoard* board, ChessPiece* pieces, int* counter)//hope this works
{
    //remember to initialize counter
    Cell* moves1 = getPossibleMovesStraight(board,pieces,counter);
    int temp= (*counter);
    (*counter)=0;
    //std::vector<Cell> moves2 = ChessPieceDiagonal::getPossibleMoves(board);
    Cell* moves2 = getPossibleMovesDiagonal(board,pieces,counter);
    Cell* finalmoves=(Cell*) malloc(sizeof(Cell)*temp+sizeof(Cell)*(*counter));//[temp+(*counter)];
    int i=0;
    while(i<temp)
    {
        finalmoves[i]=moves1[i];
        i++;
    }
    i=0;
    while(i<(*counter))
    {
        finalmoves[i+temp]=moves2[i];
        i++;
    }

    //remember to update the counter
    (*counter)=(*counter)+temp;
    free(moves1);
    free(moves2);
    //moves1.insert(moves1.end(), moves2.begin(), moves2.end());
    return finalmoves;
}

