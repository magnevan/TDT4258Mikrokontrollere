// kontrollert av eirikflogard

#ifndef CHESS_PIECE_H_
#define CHESS_PIECE_H_

#include "chess_cell.h"
#include "piece_types.h"
#include "color_types.h"

//#include "chess_board.h"

typedef struct ChessBoard ChessBoard;
  struct ChessBoard;//forward declaration of chessboard

 /* enum piecePoint {KING_POINTS = 1000, QUEEN_POINTS = 517, ROOK_POINTS = 129,
		   BISHOP_POINTS = 33, KNIGHT_POINTS = 16, PAWN_POINTS = 2};//may be removed*/
static int piece_points[] = {1000, 197, 127, 77, 67, 6};
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
  //public:
    ChessPiece* ChessPiece1();
    ChessPiece* ChessPiece2(pieceType ptype, colorType pcolor, Cell startpos);
    //virtual ~ChessPiece(); no destructor, no virtrual

    ChessPiece* createPiece(pieceType ptype, colorType pcolor,
				   Cell startpos);//static? still ok?

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


  //class ChessPieceStraight : virtual public ChessPiece
  //{
    //bool validMoveStraight(ChessBoard & board, Cell to);
  void getMovesStraight(ChessBoard* board, ChessPiece* pieces,
    Cell* moves, bool vertical, bool rightOrUp, int* counter);
  //public:
   //ChessPieceStraight();
    //ChessPieceStraight(pieceType ptype, colorType pcolor, Cell startpos);
  bool validMoveStraight(ChessBoard* board, ChessPiece* pieces, Cell to);
  Cell* getPossibleMovesStraight(ChessBoard* board, ChessPiece* pieces, int* counter);
  //};


  //class ChessPieceDiagonal : virtual public ChessPiece
 // {
    //bool validMoveDiagonal(ChessBoard & board, Cell to);
  void getMovesDiagonal(ChessBoard* board, ChessPiece* pieces,
    Cell* moves, bool upwards, bool right, int* counter);
  //public:
    //ChessPieceDiagonal();
    //ChessPieceDiagonal(pieceType ptype, colorType pcolor, Cell startpos);
    bool validMoveDiagonal(ChessBoard* board, ChessPiece* pieces, Cell to);
  Cell* getPossibleMovesDiagonal(ChessBoard* board, ChessPiece* pieces, int* counter);
  //};

  //class ChessPieceKing : public ChessPiece
  //{
  //public:
    //ChessPieceKing();
    //ChessPieceKing(colorType pcolor, Cell startpos);

  bool validMoveKing(ChessBoard* board, ChessPiece* pieces, Cell to);
  bool bigCastling(ChessBoard* board, ChessPiece* pieces, Cell ownPos);
  bool smallCastling(ChessBoard* board, ChessPiece* pieces, Cell ownPos);
  Cell* getPossibleMovesKing(ChessBoard* board, ChessPiece* pieces, int* counter);
  //};

  //class ChessPieceQueen : public ChessPieceStraight, public ChessPieceDiagonal
 // {
 // public:
    //ChessPieceQueen();
    //ChessPieceQueen(colorType pcolor, Cell startpos);
    //virtual ~ChessPieceQueen();

  bool validMoveQueen(ChessBoard* board,ChessPiece* pieces, Cell to);
  Cell* getPossibleMovesQueen(ChessBoard* board, ChessPiece* pieces, int* counter);
 // };

 // class ChessPieceRook : public ChessPieceStraight
  //{
  //????  void getMoves(ChessBoard & board, std::vector<Cell> & moves,
		//  bool vertical, bool right);
  //public:
    //ChessPieceRook();
    //ChessPieceRook(colorType pcolor, Cell startpos);

    
    /*virtual std::vector<Cell> getPossibleMoves(ChessBoard & board);
    virtual bool validMove(ChessBoard & board, Cell to);*/
  //};

  //class ChessPieceBishop : public ChessPieceDiagonal
 // {
 // public:
   // ChessPieceBishop();
  //  ChessPieceBishop(colorType pcolor, Cell startpos);

    /*virtual std::vector<Cell> getPossibleMoves(ChessBoard & board);
    virtual bool validMove(ChessBoard & board, Cell to);*/
  //};

 // class ChessPieceKnight : public ChessPiece
  //{
   //const int movePatterns[4][2];
    static const int knightmovePatterns[4][2] =
    {{-2, -1}, {-1, -2}, {1, -2}, {2,-1}};
  //public:
    //ChessPieceKnight();
    //ChessPieceKnight(colorType pcolor, Cell startpos);

    bool validMoveKnight(ChessBoard* board, Cell to, ChessPiece* piecen);
 Cell* getPossibleMovesKnight(ChessBoard* board, ChessPiece* pieces, int* counter);
  Cell* getCellsInKnightMovePattern(Cell from,ChessPiece* pieces, int* counter);
  //};

 // class ChessPiecePawn : public ChessPiece
 // {
 // public:
  //  ChessPiecePawn();
   // ChessPiecePawn(colorType pcolor, Cell startpos);

  bool validMovePawn(ChessBoard* board, Cell pos, ChessPiece* piece);//careful with references;
  Cell* getPossibleMovesPawn(ChessBoard* board,ChessPiece* piece, int* movinc);
 // };


#endif
