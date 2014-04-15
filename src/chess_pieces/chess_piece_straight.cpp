// Kontrollert av eirik flogard



#include "../chess_board.h"
#include "../chess_piece.h"
//#include "chess_piece_straight.h"
#include "../chess_rules.h"

//#include <iostream>



  Cell* getPossibleMovesStraight(ChessBoard* board, ChessPiece* pieces, int* counter)
  {
    Cell* moves= (Cell*) malloc(sizeof(Cell)*17);//Cell[] moves;
    //counter should not be reset after a call of method
    getMovesStraight(board, pieces, moves, true, true, counter);   // Oppover
    getMovesStraight(board, pieces, moves, true, false, counter);  // Nedover
    getMovesStraight(board, pieces, moves, false, true, counter);  // Til høyre
    getMovesStraight(board, pieces, moves, false, false, counter); // Til venstre
    return moves;
  }

  bool validMoveStraight(ChessBoard* board, ChessPiece* pieces, Cell to)
  {
    Cell ownPos = getPosition(pieces);
    if (cellequals(ownPos,to) || (ownPos.colum != to.colum && ownPos.rowum != to.rowum) ||
        to.colum > 7 || to.colum < 0 || to.rowum > 7 || to.rowum < 0)
      return false;

    ChessPiece * piece;
    Cell cell;
    int col = ownPos.colum;
    int row = ownPos.rowum;

    if (ownPos.colum == to.colum) {
      bool upwards = to.rowum > ownPos.rowum;
      int rowInc = (upwards ? 1 : -1);
      row += rowInc;
      while((upwards ? (row <= to.rowum) : (row >= to.rowum)))
      {
      cell.rowum=row;
      cell.colum=col;
      piece = getPiece(col, row);
      if (piece != 0) {
          if (row != to.rowum)
            return false;
          else
            break;
        }
      row += rowInc;
      }
      /*for (; (upwards ? (row <= to.rowum) : (row >= to.rowum)); row += rowInc) {
        cell = Cell(col, row);
        piece = board.getPiece(col, row);
        if (piece != 0) {
          if (row != to.rowum)
            return false;
          else
            break;
        }
      }*/
    } else {
    bool right=true;
    if(to.colum>ownPos.colum)
    right=true;
    else
    right=false;
      //bool right = to.col > ownPos.col;
      int colInc = (right ? 1 : -1);
      col += colInc;
      while((right ? (col <= to.colum) : (col >= to.colum)))
      {
      cell.rowum=row;
      cell.colum=col;
      piece = getPiece(col, row);
        if (piece != 0) {
          if (col != to.colum)
            return false;
          else
            break;
        }
      col += colInc;
      }
      /*for(; (right ? (col <= to.colum) : (col >= to.colum)); col += colInc) {
        cell = Cell(col, row);
        piece = board.getPiece(col, row);
        if (piece != 0) {
          if (col != to.col)
            return false;
          else
            break;
        }
      }*/
    } // end of if-else

    if (piece == 0 && isCheckOnMove(board, pieces, ownPos, cell)) {
      return false;
    } else if (piece != 0 && (getColor(piece) == getColor(pieces) ||
               isCheckOnMove(board, pieces, ownPos,
                                         getPosition(piece)))) {
      return false;
    } else
      return true;
  } // end of method validMove

  void getMovesStraight(ChessBoard* board, ChessPiece* pieces,
    Cell* moves, bool vertical, bool rightOrUp, int* counter)
  {
    Cell ownPos = getPosition(pieces);
    int col = ownPos.colum;
    int row = ownPos.rowum;
    ChessPiece * piece;
    Cell cell;

    if (vertical) {
      int rowInc = (rightOrUp ? 1 : -1);
      row += rowInc;
      //for (; (rightOrUp ? (row < 8) : (row > -1)); row += rowInc) {
      while((rightOrUp ? (row < 8) : (row > -1)))
      {
        piece = getPiece(col, row);
        cell.colum=col;
        cell.rowum=row;
        if (piece == 0 && !isCheckOnMove((board), pieces, ownPos,
                                                     cell)) {
          moves[(*counter)++]=cell;//moves.push_back(Cell(col, row));
        } else if (piece != 0) {
          if (getColor(piece) != getColor(pieces) &&
              !isCheckOnMove((board), pieces, ownPos, cell))
          moves[(*counter)++]=cell;//moves.push_back(Cell(col, row));

          return;
        }
        row += rowInc;
      }      
    } else {
      int colInc = (rightOrUp ? 1 : -1);
      col += colInc;
      //for(; (rightOrUp ? (col < 8) : (col > -1)); col += colInc) {
      while((rightOrUp ? (col < 8) : (col > -1)))
      {
        piece = getPiece(col, row);
        cell.rowum=row;
        cell.colum=col;
        if (piece == 0 && !isCheckOnMove((board), pieces, ownPos,
                                                     cell)) {
          moves[(*counter)++]=cell;//moves.push_back(Cell(col, row));
        } else if (piece != 0) {
          if (getColor(piece) != getColor(pieces) &&
              !isCheckOnMove(board, pieces, ownPos, cell)) {
          moves[(*counter)++]=cell;//moves.push_back(Cell(col, row));
          }

          return;
        }
        col += colInc;
      }
    }
  } // end of method getMovesStraight(...)

