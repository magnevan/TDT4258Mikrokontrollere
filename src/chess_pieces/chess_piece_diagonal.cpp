// Kontrollert av eirik flogard

#include <vector>
#include <stdlib.h> 

#include "../chess_board.h"
#include "../chess_piece.h"
#include "../chess_rules.h"

//#include <iostream>


  /*ChessPieceDiagonal::ChessPieceDiagonal() : ChessPiece()
  {}

  ChessPieceDiagonal::ChessPieceDiagonal(pieceType ptype, colorType pcolor,
                                         Cell startpos) :
    ChessPiece(ptype, pcolor, startpos)
  {}
*/
  Cell* getPossibleMovesDiagonal(ChessBoard* board, ChessPiece* pieces, int* counter)
  {
  
    Cell* moves=malloc(sizeof(Cell)*16);
    getMovesDiagonal(board, pieces, moves, true, true, counter);   // Oppover til høyre
    getMovesDiagonal(board, pieces, moves, true, false, counter);  // Oppover til venstre
    getMovesDiagonal(board, pieces, moves, false, true, counter);  // Nedover til høyre
    getMovesDiagonal(board, pieces, moves, false, false, counter); // Nedover til venstre
    return moves;
  }

  bool validMoveDiagonal(ChessBoard* board, ChessPiece* pieces, Cell to)
  {
    Cell ownPos = (*pieces).getPosition();
    if (cellequals(ownPos, to) || ownPos.colum == to.colum || ownPos.rowum == to.rowum ||
        to.colum > 7 || to.colum < 0 || to.rowum > 7 || to.rowum < 0)
      return false;

    // Sjekker om de er i samme diagonal
    if (abs(ownPos.colum - to.colum) != abs(ownPos.rowum - to.rowum))
      return false;

    bool right = to.colum > ownPos.colum;
    bool upwards = to.rowum > ownPos.rowum;
    int colInc = (right ? 1 : -1);
    int rowInc = (upwards ? 1 : -1);
    int col = ownPos.colum + colInc;
    int row = ownPos.rowum + rowInc;


    if (col > 7 || col < 0 || row > 7 || row < 0)
      return false;

    ChessPiece * piece;
    Cell cell;
//checks if some of the diagonals are obstructed
    while ((right ? (col <= to.colum) : (col >= to.colum)) &&
           (upwards ? (row <= to.rowum) : (row >= to.rowum))) {
      //cell = Cell(col, row);
      cell.rowum=row;
      cell.colum=col;
      piece = (*board).getPiece(col, row);
      if (piece != 0) {
        if(col != to.colum || row != to.rowum)
          return false;
        else
          break;
      }
      col += colInc;
      row += rowInc;
    }
    //sanity check
    if (cell.col != to.col || cell.row != to.row) {
      return false;
    }

    if (piece == 0 && isCheckOnMove((*board), pieces, ownPos, cell)) {
      return false;
    } else if (piece != 0 && (piece->getColor() == (*pieces).getColor() ||
               isCheckOnMove((*board), pieces, ownPos,
                                         piece->getPosition()))) {
      return false;
    } else   
      return true;
  } // end of method validMove

  void getMovesDiagonal(ChessBoard* board, ChessPiece* pieces
    Cell* moves, bool upwards, bool right, int* counter)
  {
    Cell ownPos = getPosition(pieces);
    int colInc = (right ? 1 : -1);
    int rowInc = (upwards ? 1 : -1);
    int col = ownPos.colum + colInc;
    int row = ownPos.rowum + rowInc;
    Cell cell;
    cell.colum=col;
    cell.rowum=row;

    ChessPiece * piece;

    while ((right ? (col < 8) : (col > -1)) &&
           (upwards ? (row < 8) : (row > -1))) {
      piece = (*board).getPiece(col, row);
      cell.rowum=row;
      cell.colum=col;
      if (piece == 0 && !isCheckOnMove((*board), pieces, ownPos,
                                                   cell)) {
        moves[(*counter)++]=cell;//moves.push_back(Cell(col, row));
      } else if (piece !=0) {
        if (getColor(piece) != getColor(pieces) &&
            !isCheckOnMove((*board), pieces, ownPos,
                                       getPosition(piece))) {
         moves[(*counter)++]=cell; //moves.push_back(Cell(col, row));
        }

        return;
      }

      col += colInc;
      row += rowInc;
    }

  } // end of method ChessPieceDiagonal::getMovesDiagonal(...)

