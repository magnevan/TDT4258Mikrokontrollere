// Kontrollert av eirik Flogard



#include "chess_board.h"
#include "chess_piece.h"
#include "chess_rules.h"


  /*const int knightmovePatterns[4][2] =
    {{-2, -1}, {-1, -2}, {1, -2}, {2,-1}};*/



  bool validMoveKnight(ChessBoard* board, Cell to, ChessPiece* piecen)
  {
    if (to.colum > 7 || to.colum < 0 || to.rowum > 7 || to.rowum < 0)
      return false;

    Cell ownPos = getPosition(piecen);
int i;
    for (i = 0; i < 4; i++) {
      if (knightmovePatterns[i][0] + ownPos.colum == to.colum &&
          (knightmovePatterns[i][1] + ownPos.rowum == to.rowum ||
           knightmovePatterns[i][1]*-1 + ownPos.rowum == to.rowum)) {
        ChessPiece * piece = getPiece(to.colum, to.rowum);
        Cell cell;
        cell.colum=to.colum;
        cell.rowum=to.rowum;
        if (piece == 0 && isCheckOnMove(board, piecen, ownPos,
                                                    cell)) {
          return false;
        } else if (piece != 0 && (getColor(piece) == getColor(piecen) ||
                   isCheckOnMove(board, piecen, ownPos,
                                             cell))) {
          return false;
        } else
          return true;
      }
    }
   
    return false;
  } // end of method validdMove(ChessBoard & board, Cell to)
  
 Cell* getPossibleMovesKnight(ChessBoard* board, ChessPiece* pieces, int* counter)
  {
    Cell ownPos = getPosition(pieces);
    Cell* moves=(Cell*) malloc(sizeof(Cell)*8);//Cell moves[8];//std::vector<Cell> moves;
    int movecount=0;
    ChessPiece * piece;

    (*counter)=0;
   Cell* cellsInPattern = getCellsInKnightMovePattern(ownPos, pieces, counter);
    //std::vector<Cell>::iterator it = cellsInPattern.begin();
    int i=0;
    //counter er her antall moves fra cellsinpattern
    while(i<(*counter))
    {
    piece = getPiece(cellsInPattern[i].colum, cellsInPattern[i].rowum);
          if (piece == 0 && !isCheckOnMove(board, pieces, ownPos,
                                                   cellsInPattern[i])) {
        moves[movecount++]=cellsInPattern[i];
      } else if (piece != 0 && getColor(piece) != getColor(pieces) &&
                 !isCheckOnMove((board), pieces, ownPos,
                                            cellsInPattern[i])) {
        moves[movecount++]=cellsInPattern[i];
      }
    i++;
    }
    (*counter)=movecount;
    free(cellsInPattern);
   /* for (; it != cellsInPattern.end(); it++) {
      piece = board.getPiece(it->col, it->row);
      if (piece == 0 && !ChessRules::isCheckOnMove(board, this, ownPos,
                                                   Cell(it->col, it->row))) {
        moves.push_back(*it);
      } else if (piece != 0 && piece->getColor() != getColor() &&
                 !ChessRules::isCheckOnMove(board, this, ownPos,
                                            Cell(it->col, it->row))) {
        moves.push_back(*it);
      }
    }*/

    return moves;
  } // end of method getPossibleMoves(ChessBoard & board)

  Cell* getCellsInKnightMovePattern(Cell from,ChessPiece* pieces, int* counter)
  {
    //Cell cells[8];
    Cell* cells=(Cell*) malloc(sizeof(Cell)*8);
    Cell cell;
    cell.colum=from.colum;
    cell.rowum=from.rowum;
    (*counter)=0;
    int col, row;
int i;
    for (i = 0; i < 4; i++) {
      col = knightmovePatterns[i][0] + from.colum;
      if (col < 8 && col > -1) {
        row = knightmovePatterns[i][1] + from.rowum;
        if(row < 8 && row > -1)
        {
        cell.colum=col;
        cell.rowum=row;
          cells[(*counter)++]=cell;
          }
        row = knightmovePatterns[i][1]*-1 + from.rowum; 
        if(row < 8 && row > -1)
        {
        cell.colum=col;
        cell.rowum=row;
           cells[(*counter)++]=cell;//cells.push_back(Cell(col, row));
          }
      }
    }

    return cells;
  }

