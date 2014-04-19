//kontrollert av eirik flgoard


#include "chess_board.h"
#include "chess_piece.h"
#include "chess_rules.h"





  bool smallCastling(ChessBoard* board, ChessPiece* pieces, Cell ownPos)
  {

    if (cellequals(ownPos,getStartPosition((pieces)))) {
      ChessPiece** piecevector = getPieces(getColor((pieces)),board);//found in board
      int piecevectorlength=(*board).pieceslength[getColor((pieces))];
      int i=0;
      //for(int i=0; i<piecevectorlength; i++)//fix size()
      while(i<piecevectorlength)
      {
        if(cellequals(getPosition(piecevector[i]),
           getStartPosition(piecevector[i])) &&
           getType(piecevector[i])==ROOK) {
          int rad=ownPos.rowum;
          Cell rookpos=getPosition(piecevector[i]);
          if(rookpos.colum==0)
          {i++;
            continue;
            }
          int j=ownPos.colum+1;
         // for(int j=ownPos.col+1; j<rookpos.col; j++)//liten rokkade, checking for obstructions
         while(j<rookpos.colum)
          {
            if(getPiece(j,rad)!=0)
              return false;  
              j++;
          }
          return true;
          //its a move if it gets here
         
        }
        i++;
      }
      return false;
    }
    return false;
  }

  bool bigCastling(ChessBoard* board, ChessPiece* pieces, Cell ownPos)
  {
  //upper if check is a redundant check for better performance. There will be no check for castling if the piece already has moved.
    if(cellequals(ownPos, getStartPosition(pieces))) {
      ChessPiece** piecevector = getPieces(getColor((pieces)),board);//must fix this later
      int piecevectorlength=(*board).pieceslength[getColor((pieces))];
      int i=0;
      //for(int i=0; i<piecevectorlength; i++)//fix size()
      
      while(i<piecevectorlength)
        {

          if(cellequals(getPosition(piecevector[i]),
           getStartPosition(piecevector[i])) &&
           getType(piecevector[i])==ROOK)
          {
            int rad=ownPos.rowum;
            Cell rookpos=getPosition(piecevector[i]);
            if(rookpos.colum==7)//wrong rook
            {
            i++;
              continue;
              }
              int j=rookpos.colum+1;
              
            //for(int j=rookpos.col+1; j<ownPos.col; j++)//utfør stor rokkade
            while(j<ownPos.colum)
            {
              if(getPiece(j,rad)!=0)
                return false;
                j++;
            }
            return true;
            //its a confirmed valid move if it gets here
          }
          i++;
        }
      return false;
      }

    return false;
  }

  bool validMoveKing(ChessBoard* board, ChessPiece* pieces, Cell to)
  {
    Cell ownPos = getPosition(pieces);
    Cell cell;
    if (cellequals(ownPos,to) || to.colum > 7 || to.rowum < 0 || to.rowum > 7 || to.rowum < 0)
      return false;

    bool upwards = (to.rowum > ownPos.rowum);
    bool right = (to.colum > ownPos.colum);

    int col = ownPos.colum;
    int row = ownPos.rowum;
    cell.rowum=row;
    cell.colum=col;
    
    //we need to consider diagonals as well
    if (right)
      col++;
    else if (to.colum < ownPos.colum)
      col--;

    if (upwards)
      row++;
    else if (to.rowum < ownPos.rowum)
      row--;

    // TODO: Check castling
    if(to.rowum==ownPos.rowum && to.colum==(ownPos.colum+2)) {
      //liten rokkade,ischeckonmove
      if(smallCastling(board,pieces,ownPos)) {
      cell.colum=ownPos.colum+2;
      cell.rowum=ownPos.rowum;
        if(!isCheckOnMove(board, pieces, ownPos,
                                      cell))
          return true;
        return false;
      }
      return false; //not fullfilling requriements for the caslting
    } else if(to.rowum==ownPos.rowum&&to.colum==(ownPos.colum-3)) {
      //ischeckonmove
      if(bigCastling(board,pieces,ownPos))
        {cell.colum=ownPos.colum-3;
        cell.rowum=row;
          if(!isCheckOnMove(board, pieces, ownPos,
                                        cell))
            return true;
          return false;
        }return false;
    }
    
    if (col != to.colum || row != to.rowum)
      return false;

    ChessPiece * piece =getPiece(col, row);
    cell.rowum=row;
    cell.colum=col;
    if (piece == 0 && isCheckOnMove(board, pieces, ownPos,
                                                cell)) {
      return false;
    } else if (piece != 0 && (getColor(piece) == getColor(pieces) ||
                          isCheckOnMove(board, pieces, ownPos, cell))) {
      return false;
    } else
      return true;
  }
  
  Cell* getPossibleMovesKing(ChessBoard* board, ChessPiece* pieces, int* counter)
  {
    Cell ownPos = getPosition(pieces);
    Cell* moves=(Cell*) malloc(sizeof(Cell)*15);//we must use malloc, because the array will die inside the scope
    Cell cell;
    // TODO: Check castling

    int col = ownPos.colum;
    int row = ownPos.rowum;
      
    if(smallCastling(board, pieces,ownPos))
    {
    cell.rowum=ownPos.rowum;
    cell.colum=ownPos.colum+2;
      if(!isCheckOnMove(board, pieces, ownPos,
                                    cell))
        moves[(*counter)++]=cell;//moves.push_back(Cell(col+2,row));
    }
    
    if(bigCastling(board,pieces,ownPos)) {
    cell.rowum=ownPos.rowum;
    cell.colum=ownPos.colum-3;

      if(!isCheckOnMove(board, pieces, ownPos,
                                    cell))
        moves[(*counter)++]=cell;//moves.push_back(Cell(col+2,row));
    }

    int maxCol = (col == 7 ? col : col + 1);
    int maxRow = (row == 7 ? row : row + 1);

    int minCol = (col == 0 ? col : col - 1);
    int minRow = (row == 0 ? row : row - 1);

    ChessPiece * piece;

   // for (row = minRow; row <= maxRow; row++) {
   row=minRow;
   while(row<=maxRow){
      //for (col = minCol; col <= maxCol; col++) {

      col=minCol;
      while(col<=maxCol){
      cell.colum=col;
      cell.rowum=row;
        if (cellequals(ownPos, cell))
        {
        col++;
          continue;
          }

        piece = getPiece(col, row);

        if (piece == 0 && !isCheckOnMove(board, pieces, ownPos,
                                                     cell)) {
        moves[(*counter)++]=cell; //moves.push_back(Cell(col, row));
        } else if (piece != 0 && getColor(piece) != getColor(pieces) &&
                 !isCheckOnMove(board, pieces, ownPos,
                                            cell)) {
        moves[(*counter)++]=cell; //moves.push_back(Cell(col, row));
        }
        col++;
      }
      row++;
    }
    return moves;
  }


