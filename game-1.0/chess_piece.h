// kontrollert av eirikflogard

#ifndef CHESS_PIECE_H_
#define CHESS_PIECE_H_

#include "chess_cell.h"
#include "piece_types.h"
#include "color_types.h"

//#include "chess_board.h"

typedef struct ChessBoard ChessBoard;
  struct ChessBoard;//forward declaration of chessboard

static const int piece_points[] = {1000, 197, 127, 77, 67, 6};
typedef struct ChessPiece ChessPiece;
  struct ChessPiece
  {
    pieceType type;
    colorType color;
    int points;
    Cell position;
    Cell startPosition;
    int moved;
  };

    ChessPiece* ChessPiece1();
    ChessPiece* ChessPiece2(pieceType ptype, colorType pcolor, Cell startpos);

    //creates a new piece
    ChessPiece* createPiece(pieceType ptype, colorType pcolor,
				   Cell startpos);

    pieceType getType(ChessPiece* piece);
    colorType getColor(ChessPiece* piece);
    int getPoints(ChessPiece* piece);
    Cell getPosition(ChessPiece* piece);
    void setPosition(Cell newpos, ChessPiece* piece);
    Cell getStartPosition(ChessPiece* piece);
    int getMovedCount(ChessPiece* piece);

    bool validMove(ChessBoard * board, Cell to, ChessPiece* piece);//gjør somme som possible moves
    Cell* getPossibleMoves(ChessBoard * board, ChessPiece* piece, int* counter); //remove virtrual, la denne metoden sjekke brikketype og kalle riktig posmoves
  //getpossiblemoves returns dynamic allocated array. must be freed


//all the declarations below are methods belonging to the different pieces
  void getMovesStraight(ChessBoard* board, ChessPiece* pieces,
    Cell* moves, bool vertical, bool rightOrUp, int* counter);

  bool validMoveStraight(ChessBoard* board, ChessPiece* pieces, Cell to);
  Cell* getPossibleMovesStraight(ChessBoard* board, ChessPiece* pieces, int* counter);




  void getMovesDiagonal(ChessBoard* board, ChessPiece* pieces,
    Cell* moves, bool upwards, bool right, int* counter);
    bool validMoveDiagonal(ChessBoard* board, ChessPiece* pieces, Cell to);
  Cell* getPossibleMovesDiagonal(ChessBoard* board, ChessPiece* pieces, int* counter);


  bool validMoveKing(ChessBoard* board, ChessPiece* pieces, Cell to);
  bool bigCastling(ChessBoard* board, ChessPiece* pieces, Cell ownPos);
  bool smallCastling(ChessBoard* board, ChessPiece* pieces, Cell ownPos);
  Cell* getPossibleMovesKing(ChessBoard* board, ChessPiece* pieces, int* counter);


  bool validMoveQueen(ChessBoard* board,ChessPiece* pieces, Cell to);
  Cell* getPossibleMovesQueen(ChessBoard* board, ChessPiece* pieces, int* counter);

    static const int knightmovePatterns[4][2] =
    {{-2, -1}, {-1, -2}, {1, -2}, {2,-1}};


    bool validMoveKnight(ChessBoard* board, Cell to, ChessPiece* piecen);
 Cell* getPossibleMovesKnight(ChessBoard* board, ChessPiece* pieces, int* counter);
  Cell* getCellsInKnightMovePattern(Cell from,ChessPiece* pieces, int* counter);


  bool validMovePawn(ChessBoard* board, Cell pos, ChessPiece* piece);
  Cell* getPossibleMovesPawn(ChessBoard* board,ChessPiece* piece, int* movinc);



#endif
