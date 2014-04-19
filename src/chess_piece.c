// kontrollert av eirik

#include "chess_board.h"
#include "chess_rules.h"
#include "chess_piece.h"


//#include <iostream>


 ChessPiece* ChessPiece1() //: type(EMPTY), color(BLACK), points(0),
                            // position(0, 0), startPosition(0, 0), moved(false)
  {
  
  ChessPiece* ChessPiece1=(ChessPiece *) malloc(sizeof(ChessPiece));
  (*ChessPiece1).type=EMPTY;
  (*ChessPiece1).color=BLACK;
  (*ChessPiece1).points=0;
  (*ChessPiece1).position.colum=0;
  (*ChessPiece1).position.rowum=0;
  (*ChessPiece1).startPosition.colum=0;
  (*ChessPiece1).startPosition.rowum=0;
  (*ChessPiece1).moved=0;
  return ChessPiece1;
  
  }

 ChessPiece* ChessPiece2(pieceType ptype, colorType pcolor, Cell startpos) //:
   // type(ptype), color(pcolor), position(startpos), points(piece_points[ptype]),
   // startPosition(startpos), moved()
  {
    ChessPiece* ChessPiece1=(ChessPiece*) malloc(sizeof(ChessPiece));
  (*ChessPiece1).type=ptype;
  (*ChessPiece1).color=pcolor;
  (*ChessPiece1).points=piece_points[ptype];//check
  (*ChessPiece1).position.colum=startpos.colum;
  (*ChessPiece1).position.rowum=startpos.rowum;
  (*ChessPiece1).startPosition.colum=startpos.colum;
  (*ChessPiece1).startPosition.rowum=startpos.rowum;
  (*ChessPiece1).moved=0;//maybe not ok
  return ChessPiece1;
  
  }

 // ChessPiece::~ChessPiece() we need to free those stupid chesspieces


  ChessPiece* createPiece(pieceType ptype, colorType pcolor,
                                      Cell startpos)
  {
    switch(ptype) {
    case PAWN:
    return ChessPiece2(ptype,pcolor,startpos);
      //return new ChessPiecePawn(pcolor, startpos);
    case KNIGHT:
      //return new ChessPieceKnight(pcolor, startpos);
      return ChessPiece2(ptype,pcolor,startpos);
    case BISHOP:
     // return new ChessPieceBishop(pcolor, startpos);
      return ChessPiece2(ptype,pcolor,startpos);
    case ROOK:
      //return new ChessPieceRook(pcolor, startpos);
      return ChessPiece2(ptype,pcolor,startpos);
    case QUEEN:
     //return new ChessPieceQueen(pcolor, startpos);
      return ChessPiece2(ptype,pcolor,startpos);
    default:
      //return new ChessPieceKing(pcolor, startpos);
      return ChessPiece2(ptype,pcolor,startpos);
    }
  }

  pieceType getType(ChessPiece* piece)
  {
    return (*piece).type;
  }

  colorType getColor(ChessPiece* piece)
  {
    return (*piece).color;
  }

  int getPoints(ChessPiece* piece)
  {
    return (*piece).points;
  }

  Cell getPosition(ChessPiece* piece)
  {
    return (*piece).position;
  }

  void setPosition(Cell newpos, ChessPiece* piece)
  {
    (*piece).position = newpos;
    (*piece).moved++;
  }

  Cell getStartPosition(ChessPiece* piece)
  {
    return (*piece).startPosition;
  }

  int getMovedCount(ChessPiece* piece)
  {
    return (*piece).moved;
  }
  
  bool validMove(ChessBoard* board, Cell to, ChessPiece* piece)
  {
  pieceType ptype=getType(piece);
      switch(ptype) {
    case PAWN:
   return validMovePawn(board, to, piece);
    case KNIGHT:
   return validMoveKnight(board, to, piece);
    case BISHOP:
   return validMoveDiagonal(board, piece,to);
    case ROOK:
   return validMoveStraight(board, piece,to);
    case QUEEN:
   return validMoveQueen(board, piece,to);
    default:
   return validMoveKing(board, piece,to);
    }
  
  }
  //TODO trenger å vite lengden på arrayene. Å reallokere er ineffektivt
  Cell* getPossibleMoves(ChessBoard* board, ChessPiece* piece, int* counter)
  {
      
    pieceType ptype=getType(piece);
      switch(ptype) {
    case PAWN:
   return getPossibleMovesPawn( board,piece,counter);
    case KNIGHT:
   return getPossibleMovesKnight( board,piece,counter);
    case BISHOP:
   return getPossibleMovesDiagonal( board,piece,counter);
    case ROOK:
   return getPossibleMovesStraight( board,piece,counter);
    case QUEEN:
   return getPossibleMovesQueen( board,piece,counter);
    default:

   return getPossibleMovesKing( board,piece,counter);
    }
  
  }

