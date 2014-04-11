// Kontrollert av Eirik Flogard



#include "chess_board.h"
#include "chess_rules.h"

#include <iostream>

  bool win(ChessBoard* board, colorType lastColorMove)
  {
    colorType nextColorMove = colorType(1 - lastColorMove);
    return isCheck(nextColorMove) && !hasMoves(board, nextColorMove);
  }

  bool stalemate(ChessBoard* board, colorType lastColorMove)//check for remis
  {
  colorType nextColorMove;
  if(lastColorMove==1)
  nextColorMove=0;
  else
  nextColorMove=1;
    //colorType nextColorMove = colorType(1 - lastColorMove);
    return !board.isCheck(nextColorMove) && !hasMoves(board, nextColorMove);
  }

  
  bool tie(ChessBoard* board)
  {
    ChessPiece** piecesBlack = getPieces(BLACK);
     ChessPiece** piecesWhite = getPieces(WHITE);//board file
    pieceType pType;

    //if (piecesBlack.size() == 1 && piecesWhite.size() == 1)
    if((*board).pieceslength[BLACK]==1&&(*board).pieceslength[WHITE]==1)
      return true; // Konge mot konge

    //if (piecesBlack.size() == 1) {
    if((*board).pieceslength[BLACK]==1)
      if ((*board).pieceslength[WHITE] == 2) {
        pType = getType(piecesWhite[1]);
        if (pType == KNIGHT || pType == BISHOP)
          return true;
      }
    } //else if (piecesWhite.size() == 1) {
    else if((*board).pieceslength[WHITE]==1){
      //if (piecesBlack.size() == 2) {
      if(*board).pieceslength[BLACK]==2){
        pType =getType( piecesBlack[1]);
        if (pType == KNIGHT || pType == BISHOP)
          return true;
      }
    } //else if (piecesBlack.size() == 2 && piecesWhite.size() == 2) {
    else if((*board).pieceslength[BLACK]==2&&(*board).pieceslength[WHITE]==2){
      ChessPiece * pieceBlack = piecesBlack[1];
      ChessPiece * pieceWhite = piecesWhite[1];
      //if (pieceBlack->getType() == BISHOP && pieceWhite->getType() == BISHOP &&
        //  (pieceBlack->getStartPosition().col % 2) != 
          //(pieceWhite->getStartPosition().col % 2)) {
          if(getType(pieceBlack)==BISHOP&&getType(pieceWhite)==BISHOP&&
          (getStartPosition(pieceBlack).colum%2)!=(getStartPosition(pieceWhite).colum%2)){
        return true;
      }
    }

    return !hasMoves(board, BLACK) && !hasMoves(board, WHITE);
  }

  bool hasMoves(ChessBoard* board, colorType color)
  {
    bool moves = false;
    ChessPiece** pieces = getPieces(color);
    int piecelength=(*board).pieceslength[color]
    //std::vector<ChessPiece*>::iterator it;
int i=0;
    //for (it = pieces.begin(); it != pieces.end(); it++) {
    while(i<piecelength){
    int counter=0;
    getPossibleMoves( board, pieces[i], &counter);
     // if (getPossibleMoves(board).size() > 0) {
     if(counter>0)
        moves = true;
        break;
      }
      i++;
    }

    return moves;
  }

  bool isCheckOnMove(ChessBoard* board,
                                 ChessPiece * pieceToMove, Cell from, Cell to)
  {   
    //bool check = false;
    bool hasMoved = (getPiece(to.colum, to.rowum) == pieceToMove);
    colorType kingColor;
 
    if (!hasMoved) {
      kingColor = getColor(pieceToMove);

      // Motstanders brikke som skal tas i en simulering av et trekk
      bool capturedPiece =getPiece(to.col, to.row) != 0;

      movePieceWithoutCheck(pieceToMove, to);
      bool check = isCheck(board, kingColor);
      movePieceWithoutCheck(pieceToMove, from);

      if (capturedPiece) {
       placeBackLastCapturedPiece(colorType(1 - getColor(pieceToMove)),board);
      }

      return check;
    }

    kingColor =  colorType(1 - getColor(pieceToMove));
    Cell kingPos = getPosition(getPieces(kingColor)[0]);

    // Sjekker om motstanderns konge er i sjakk som følge av trekket
    if (validMove(board, kingPos,pieceToMove))
      return true;

    // Sjekker om motstanderns konge er i sjakk av de andre brikkene på grunn av trekket

    if (kingPos.rowum > from.rowum) {
      if (kingPos.colum == from.colum)
        return isCheckStraight(board, kingColor, true, false);//check
      else {
        if (abs(kingPos.colum - from.colum) != abs(kingPos.rowum - from.rowum))
           return false;

        if (kingPos.colum > from.colum)
          return isCheckDiagonal(board, kingColor, false, false);//check
        else
          return isCheckDiagonal(board, kingColor, false, true);
      }
    } else if (kingPos.rowum < from.rowum) {
      if (kingPos.colum == from.colum)
        return isCheckStraight(board, kingColor, true, true);//check
      else {
        if (abs(kingPos.colum - from.colum) != abs(kingPos.rowum - from.rowum))
           return false;

        if (kingPos.colum > from.colum)
          return isCheckDiagonal(board, kingColor, true, false);
        else
          return isCheckDiagonal(board, kingColor, true, true);
      }
    } else { // kingPosOpp.row == from.row
      if (kingPos.colum > from.colum)
        return isCheckStraight(board, kingColor, false, false);
      else
        return isCheckStraight(board, kingColor, false, true);
    }
  } // end of method :isCheckOnNextMove(...)

  bool isCheck(ChessBoard* board, colorType kingColor)
  {
    // TODO: Bør bruke brikkenes validMove-metode istedenfor?
    return (
      // Sjekker vertikalt for motstanders konge, dronning eller tårn
      isCheckStraight(board, kingColor, true, true) ||
      isCheckStraight(board, kingColor, true, false) ||
      // Sjekker horisontalt for motstanders konge, dronning eller tårn
      isCheckStraight(board, kingColor, false, true) ||
      isCheckStraight(board, kingColor, false, false) ||
      // Sjekker diagonalt for motstanders konge, dronning, løper eller bonde
      isCheckDiagonal(board, kingColor, true, true) ||
      isCheckDiagonal(board, kingColor, true, false) ||
      isCheckDiagonal(board, kingColor, false, true) ||
      isCheckDiagonal(board, kingColor, false, false) ||
      // Sjekker om motstanders springer kan ta kongen
      isCheckKnight(board, kingColor)
    );
  }

  bool isCheckStraight(ChessBoard* board, colorType kingColor,
                                   bool vertical, bool rightOrUp)
  {
    Cell kingPos = getPosition(getPieces(kingColor,board)[0]);

    // TODO: Bør bruke brikkenes validMove-metode istedenfor

    int col, row;
    if (vertical) {
      col = kingPos.colum;
      row = kingPos.rowum + (rightOrUp ? 1 : -1);
      if ((rightOrUp && row > 7) || (!rightOrUp &&  row < 0))
        return false;
    } else {
      row = kingPos.rowum;
      col = kingPos.colum + (rightOrUp ? 1 : -1);
      if ((rightOrUp && col > 7) || (!rightOrUp && col < 0))
        return false;
    }

    if (col > 7 || col < 0 || row > 7 || row < 0)
      return false;


    ChessPiece * piece;
    pieceType type;
    piece = getPiece(col, row);
    if (piece != 0) {
      type = getType(piece);
      if(getColor(piece) == kingColor)
        return false;

      if (type == KING)//oponent king is on adjacent square
        return true;
    }
   
    int inc = (rightOrUp ? 1 : -1);
    int colOrRow = (vertical ? row : col);

    //for (; (rightOrUp ? (colOrRow < 8) : (colOrRow >= 0)); colOrRow += inc) {
    while(rightOrUp ? (colOrRow < 8) : (colOrRow >= 0)){
      if (vertical) {
        piece = getPiece(col, colOrRow);
        //std::cout << "col/row: " << char(65 + col) << colOrRow + 1
        //<< std::endl;
      }
      else {
        //std::cout << "col/row: " << char(65 + colOrRow) << row + 1
        //<< std::endl;
        piece = getPiece(colOrRow, row);
      }
      
      if (piece != 0 ) {
        if(getColor(piece) == kingColor)
          return false;

        type = getType(piece);

        if (type == QUEEN || type == ROOK)
          return true;
        else
          return false;
      }
      colOrRow += inc;
    }

    return false;
  } // end of method isCheckStraight(...)


  bool isCheckDiagonal(ChessBoard* board, colorType kingColor,
                                   bool upwards, bool right)
  {
    Cell kingPos = getPosition(getPieces(kingColor,board)[0]);

    int colInc = (right ? 1 : -1);
    int rowInc = (upwards ? 1 : -1);
    int col = kingPos.colum + colInc;
    int row = kingPos.rowum + rowInc;
    if (col > 7 || col < 0 || row > 7 || row < 0)
      return false;

    ChessPiece * king = getPieces(kingColor,board)[0];
    bool pawnMovesDown = (getStartPosition(king).row == 0);
    ChessPiece * piece;
    pieceType type;

    piece = getPiece(col, row);
    if (piece != 0) {
      type = getType(piece);
      if(getColor(piece) == kingColor)
        return false;

      if(type == KING || type == PAWN)
        return true;
    }

    while ((right ? (col < 8) : (col > -1)) &&
           (upwards ? (row < 8) : (row > -1))) {
      piece = getPiece(col, row);
      if (piece != 0 ) {
        if(getColor(piece) == kingColor)
          return false;

        type = getType(piece);
        if (type == QUEEN || type == BISHOP)
          return true;
        else
          return false;
      }

      col += colInc;
      row += rowInc;
    }

    return false;
  } // end of method isCheckDiagonal(...)

  bool isCheckKnight(ChessBoard* board,
                                 colorType kingColor)
  {
    Cell kingPos =getPosition(getPieces(kingColor,board)[0]);
    ChessPiece * piece;
int counter=0;
    Cell* cellsInPattern =
      getCellsInKnightMovePattern(kingPos,piece,&counter);//ChessPieceKnight free

    //std::vector<Cell>::iterator it = cellsInPattern.begin();
    int i=0;
    //for (; it != cellsInPattern.end(); it++) {
    while(i<counter){
      //piece = board.getPiece(it->col, it->row);
      piece = getPiece(cellsInPattern[i].colum, cellsInPattern[i].rowum);
      if (piece != 0 && getColor(piece) != kingColor &&
          getType(piece) == KNIGHT) {
          free(cellsInPattern);
        return true;//checked by oponents knight
      }
      i++;
    }
    free(cellsInPattern);
    return false;
  } // end of method isCheckKnight(...)

  void promotion(ChessBoard* board,colorType color, ChessPiece* piece)//check after moving a peasant
  {
  Cell pos=getPosition(piece);
  if(getType(piece)==PAWN)
  {
  if(color==WHITE)
  {
  if(pos.rowum==7)
  {
  board.removePiece(pos,board);
  board.setPiece(QUEEN, color, pos,board);

  }
  
  }
  else
  {
  if(pos.row==0)
  {
  board.removePiece(pos); 
   board.setPiece(QUEEN, color, pos,board);
  }
  
  }
    //fjern brikke fra vektor og erstatt med dronning
  }
  }

