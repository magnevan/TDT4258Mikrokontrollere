//kontrollert av eirik flogard


#include <stdlib.h> 

#include "chess_board.h"
#include "chess_rules.h"
#include "chess_piece.h"



//Vi kan lage getpossiblemovespawn() og sjekke piecetype på gammeldagse måten
//da kan finner vi manuelt de rektige movesa til de forskjellige brikkene.

  bool validMovePawn(ChessBoard* board, Cell pos, ChessPiece* piece)//careful with references
  {
    // TODO: Optimaliser dette.
    //std::vector<Cell> moves = getPossibleMoves(board);
      int count=0;
    Cell* moves=getPossibleMovesPawn(board, piece, &count);
    //std::vector<Cell>::iterator im;
  int i=0;
    while(i<count)//sizeof array
    { 
    if(cellequals(moves[i],pos))
    {
    free(moves);
    return true;
    }
    i++;
    }
    
    free(moves);
   // for (im = moves.begin(); im != moves.end(); im++ ) {
      //if (*im == pos)
      //  return true;
    //}
    
    return false;
  }
    
  Cell* getPossibleMovesPawn(ChessBoard* board,ChessPiece* piece, int* movinc)//was originally reference here
  {
    Cell pos = getPosition(piece);
    Cell kingStartpos = getStartPosition(getPieces(getColor(piece),board)[0]);
    bool pawnMovesUp = kingStartpos.rowum == 0;
    int rowinc = (pawnMovesUp ? 1 : -1);
    int cellsFront = (abs(kingStartpos.rowum - pos.rowum) < 2 ? 2 : 1);
    Cell* moves=(Cell*) malloc(sizeof(Cell)*6);
    
    ChessPiece * pieces;
    int row = pos.rowum + rowinc;
    int i=0;
    //optimize this, unnecessary to use copying of cells into arrays
    Cell cell;
    cell.colum=pos.colum;
    cell.rowum=row;
    while(i<cellsFront)
    {
    
     if (row > 7 || row < 0)
        return moves;
        cell.rowum=row;
      pieces = getPiece(pos.colum, row);
      if (pieces != 0)
        break;

      if(!isCheckOnMove((board), piece, pos, cell))
        moves[(*movinc)++]=cell;

      row += rowinc;
    i++;
    }
   /* for (int i = 0; i < cellsFront; i++ ) {
      if (row > 7 || row < 0)
        return moves;
      pieces = (*board).getPiece(pos.col, row);
      if (pieces != 0)
        break;

      if(!ChessRules::isCheckOnMove((*board), this, pos, Cell(pos.col, row)))
        moves.push_back(Cell(pos.col, row));

      row += rowinc;
    }*/

    //this checks if a pawn can move diagonal
    if (pos.colum != 0 && pos.rowum + rowinc < 8 && pos.rowum + rowinc > -1) {
      pieces = getPiece(pos.colum - 1, pos.rowum + rowinc);
      if (pieces != 0 && getColor(pieces) != getColor(piece) &&
          !isCheckOnMove((board), piece, pos,
                                     getPosition(pieces))) {
        moves[(*movinc)++]=(getPosition(pieces));
      }
    }

    if (pos.colum != 7 && pos.rowum + rowinc < 8 && pos.rowum + rowinc > -1) {
      pieces = getPiece(pos.colum + 1, pos.rowum + rowinc);
      if (pieces != 0 && getColor(pieces) != getColor(piece) &&
          !isCheckOnMove((board), piece, pos,
                                     getPosition(pieces))) {
        moves[(*movinc)++]=(getPosition(pieces));
      }
    }

    return moves;
  }
  //the abs method is not our work
  int abs(int v) 
{
  return v * ( (v<0) * (-1) + (v>0));
}

