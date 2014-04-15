// Kontrollert av eirik

#include "chess_board.h"
#include "chess_rules.h"
#include <iostream>

  //ChessBoard::ChessBoard() : turns()
  ChessBoard* Chessboard1()
  {
  ChessBoard* chessboard=(ChessBoard *) malloc(sizeof(ChessBoard));
    (*chessboard).check[BLACK] = false;
    (*chessboard).check[WHITE] = false;
    //board = new ChessPiece ** [8];
    board=(ChessPiece***) malloc(sizeof(ChessPiece**)*8);
    int row=0;
    
    //for (int row = 0; row < 8; row++)
    while(row<8){
      //board[row] = new ChessPiece * [8];
      board[row]=(ChessPiece**) malloc(sizeof(ChessPiece*)*8);
      row++;
      }

    (*chessboard).pieces[BLACK] = (ChessPiece**) malloc(sizeof(ChessPiece*)*30);
    (*chessboard).pieces[WHITE] = (ChessPiece**) malloc(sizeof(ChessPiece*)*30);
    (*chessboard).piecesCaptured[BLACK] =(ChessPiece**) malloc(sizeof(ChessPiece*)*30);
    (*chessboard).piecesCaptured[WHITE] = (ChessPiece**) malloc(sizeof(ChessPiece*)*30);
    (*chessboard).pieceslength[0]=0;
    (*chessboard).pieceslength[1]=0;
    (*chessboard).piecescapturedlength[0]=0;
    (*chessboard).piecescapturedlength[1]=0;
    (*chessboard).turns=0;//check this
    initializeBoard(chessboard);
    
    return chessboard;
  }

  /*ChessBoard::~ChessBoard()
  {
    int col, row;
    for (row = 0; row < 8; row++) {
      for (col = 0; col < 8; col++)
        delete board[row][col];
      delete [] board[row];
    }
    delete [] board;
  }*/
    void expand(ChessBoard* chessboard, int insertspot,ChessPiece** ownPieces,colorType pcolor)//lets you insert a new piece in the middle of an array(i hope)
    {
    int i=((*chessboard).pieceslength[pcolor]-1);
    while(i>=0)
    {
    ownPieces[i+1]=ownPieces[i];
    i--;
    }
    
    (*chessboard).pieceslength[pcolor]++;
    }
  void setPiece(pieceType ptype, colorType pcolor, Cell startpos, ChessBoard* chessboard)
  {
    ChessPiece * piece = getPiece(startpos.colum, startpos.rowum);
    if (piece != 0)
      removePiece(startpos,chessboard);
    ChessPiece * newPiece = createPiece(ptype, pcolor, startpos);
//
    board[startpos.rowum][startpos.colum] = newPiece;
    ChessPiece** ownPieces = getPieces(pcolor,chessboard);
    //std::vector<ChessPiece*>::iterator it = ownPieces.begin();
    int i=0;
    
   // for (it = ownPieces.begin(); it != ownPieces.end(); it++) {
   while(i<(*chessboard).pieceslength[pcolor]){
     // if((*it)->getPoints()+(*it)->getStartPosition().col < 
       //  newPiece->getPoints()+newPiece->getStartPosition().col) {
       if(getPoints(ownPieces[i])+getStartPosition(ownPieces[i]).colum< getPoints(newPiece)+getStartPosition(newPiece).colum){//find the place in the piecearray where piece belongs
        //ownPieces.insert(it, newPiece);//we need to make room in the vector for the new piece to be put in. I would consider not doing this as bad programming practice. Bugs will occur.
        expand(chessboard,i,ownPieces,pcolor);
        ownPieces[i]=newPiece;
        return;
      }
      i++;
    }



    //ownPieces.push_back(newPiece);
    ownPieces[(*chessboard).pieceslength[pcolor]++]=newPiece;
  }

  void initializeBoard(ChessBoard* chessboard)
  {
    int col, row;
    
    colorType color = BLACK;

    // Nuller aller rutene først
    //for (row = 0; row < 8; row++) {
    row=0;
    while(row<8){
      //for (col = 0; col < 8; col++)
      col=0;
      while(col<8){
        board[row][col] = 0;//should be malloced by now
        col++;
        }
        row++;
    }

    row = 7;
    int i=0;
    
    //for (int i = 0; i < 2; i++) {
    Cell cell;
    while(i<2){
      //board[row][4] =  new ChessPieceKing(color, Cell(4, row));
      cell.rowum=row;
      cell.colum=4;
      board[row][4] = ChessPiece2(KING, color, cell);
      //(*ChessBoard).pieces[color].push_back(board[row][4]);
      (*chessboard).pieces[color][(*chessboard).pieceslength[color]++]=board[row][4];//this should hopefully be a piecepointer now to a dynamic allocateed chesspiece
      //(*ChessBoard).pieceslength[color]++;

      //board[row][3] =  new ChessPieceQueen(color, Cell(3, row));
      
      cell.rowum=row;
      cell.colum=3;
      board[row][3] = ChessPiece2(QUEEN, color, cell);
      //pieces[color].push_back(board[row][3]);
     (*chessboard).pieces[color][(*chessboard).pieceslength[color]++]=board[row][3];
      
      //board[row][7] = new ChessPieceRook(color, Cell(7, row));
       cell.rowum=row;
      cell.colum=7;
      board[row][7] = ChessPiece2(ROOK, color, cell);
      //pieces[color].push_back(board[row][7]);
     (*chessboard).pieces[color][(*chessboard).pieceslength[color]++]=board[row][7];
     
     
      //board[row][0] = new ChessPieceRook(color, Cell(0, row));
      cell.rowum=row;
      cell.colum=0;
      board[row][0] = ChessPiece2(ROOK, color, cell);
      //pieces[color].push_back(board[row][0]);
      (*chessboard).pieces[color][(*chessboard).pieceslength[color]++]=board[row][0];

      //board[row][5] = new ChessPieceBishop(color, Cell(5, row));
            cell.rowum=row;
      cell.colum=5;
      board[row][5] = ChessPiece2(BISHOP, color, cell);
      //pieces[color].push_back(board[row][5]);
      (*chessboard).pieces[color][(*chessboard).pieceslength[color]++]=board[row][5];
      //board[row][2] = new ChessPieceBishop(color, Cell(2, row));
      cell.rowum=row;
      cell.colum=2;
      board[row][2] = ChessPiece2(BISHOP, color, cell);
      //pieces[color].push_back(board[row][2]);
      (*chessboard).pieces[color][(*chessboard).pieceslength[color]++]=board[row][2];

      //board[row][6] = new ChessPieceKnight(color, Cell(6, row));
      cell.rowum=row;
      cell.colum=6;
      board[row][6] = ChessPiece2(KNIGHT, color, cell);
      //pieces[color].push_back(board[row][6]);
     (*chessboard).pieces[color][(*chessboard).pieceslength[color]++]=board[row][6];
      //board[row][1] = new ChessPieceKnight(color, Cell(1, row));
            cell.rowum=row;
      cell.colum=1;
            board[row][1] = ChessPiece2(KNIGHT, color, cell);
      //pieces[color].push_back(board[row][1]);
      (*chessboard).pieces[color][(*chessboard).pieceslength[color]++]=board[row][1];

      row = (row == 7 ? row - 1 : row + 1);

      //for (col = 7; col >= 0; col--) {
      col=7;
      while(col>=0){
       cell.rowum=row;
      cell.colum=col;
        //board[row][col] =  new ChessPiecePawn(color, Cell(col, row));
        board[row][col] = ChessPiece2(PAWN, color, cell);
        //pieces[color].push_back(board[row][col]);
      (*chessboard).pieces[color][(*chessboard).pieceslength[color]++]=board[row][col];
        col--;
      }
      if(color==BLACK)
      color=WHITE;
      else
      color=BLACK;
      //color = colorType(1 - color);
      row = (row == 6 ? 0 : 7);
      i++;
    } // end of while
  } // end of method initializeBoard()

  ChessPiece* getPiece(int col, int row)
  {
    if (col > 7 || col < 0 || row > 7 || row < 0)
      return 0;

    return board[row][col];//change board to array. MUST return a chesspiece piinter
  }

  ChessPiece*** getallPieces()
  {
  return board;
  }
  ChessPiece** getPieces(colorType color, ChessBoard* chessboard)//return all pieces belong to 1 player
  {
      return (*chessboard).pieces[color];
  }

  ChessPiece** getCapturedPieces(colorType color, ChessBoard* chessboard)
  {
    return (*chessboard).piecesCaptured[color];
  }

  int getTurns(ChessBoard* chessboard)
  {
    return (*chessboard).turns;
  }

  bool isCheck(colorType color,ChessBoard* chessboard)
  {
    return (*chessboard).check[color];
  }

  bool setCheck(colorType color, bool checkValue,ChessBoard* chessboard)
  {
    (*chessboard).check[color] = checkValue;//change to void?
   // return true;
  }
  void placeBackLastCapturedPiece(colorType color, ChessBoard* chessboard)
  {
    ChessPiece** cap_pieces = getCapturedPieces(color, chessboard);
   int capsize=(*chessboard).piecescapturedlength[color];
    if (capsize== 0)
      return;

    //ChessPiece * lastPiece = cap_pieces.back();
    ChessPiece * lastPiece=cap_pieces[capsize-1];//last captured piece
    //cap_pieces.pop_back();
    cap_pieces[capsize-1]=0;//set the chesspiece pointer to 0
    (*chessboard).piecescapturedlength[color]--;//reduce length of the vector. update the local var capsize if still used
    Cell to = getPosition(lastPiece);
    board[to.rowum][to.colum] = lastPiece;

    ChessPiece** ownPieces = getPieces(color,chessboard);
    //std::vector<ChessPiece*>::iterator it;
    int i=0;
    //for (it = ownPieces.begin(); it != ownPieces.end(); it++) {
    while(i<(*chessboard).pieceslength[color]){
 //     if((*it)->getPoints()+(*it)->getStartPosition().col < 
   //      lastPiece->getPoints()+lastPiece->getStartPosition().col) {
   if(getPoints(ownPieces[i])+getStartPosition(ownPieces[i]).colum<
   getPoints(lastPiece)+getStartPosition(lastPiece).colum){//place in vector sorted by columns and points
        //ownPieces.insert(it, lastPiece);
        expand(chessboard, i,ownPieces,color);
        ownPieces[i]=lastPiece;
        return;
      }
      i++;
    }

    //ownPieces.push_back(lastPiece);    
    ownPieces[(*chessboard).pieceslength[color]]=lastPiece;
  }
  
   void movePlayerPieceTo(Cell from, Cell to, ChessBoard* board)
  {
    ChessPiece * pieceToMove = getPiece(from.colum, from.rowum);
    if (pieceToMove == 0)
      return; // Det finnes ingen brikker på den ruten
Cell cell;
    if(getType(pieceToMove)==KING)
    {
      //stor rokkade, konge kan ikke flytte mer enn ett felt av gangen i 
      // gyldig trekk
      
      if((from.colum-to.colum)>1) {
        if(nequals(getStartPosition(pieceToMove),getPosition(pieceToMove))) {
          //omgjør liten rokkade

          //sjekk om det faktisk ligger et tårn her
          ChessPiece * castle2 = getPiece(5, from.rowum);

          //sjekk om startposisjon endres
          movePieceWithoutCheck(castle2, getStartPosition(castle2),board);

        } else{
          //kan være 1 og ikke 0, test
          cell.rowum=from.rowum;
          cell.colum=2;
          ChessPiece * castle = getPiece(0, from.rowum);
          movePieceWithoutCheck(castle, cell,board);
        }    
      } 
      else if((from.colum-to.colum)<-1)//liten rokkade
      {
        if(nequals(getStartPosition(pieceToMove),
           getPosition(pieceToMove)))//omgjør liten rokkade
          {
            //sjekk om det faktisk ligger et tårn her
            ChessPiece * castle2 = getPiece(2, from.rowum);

            //sjekk om startposisjon endres
            movePieceWithoutCheck(castle2, getStartPosition(castle2),board);

          } else {
          //kan være 1 og ikke 0, test
          cell.rowum=from.rowum;
          cell.colum=5;
          ChessPiece * castle = getPiece(7, from.rowum);
          movePieceWithoutCheck(castle, cell,board);
        }
      }
    }

    movePieceWithoutCheck(pieceToMove, to,board);//TODO check konsistens
    setCheck(getColor(pieceToMove), false, board);
    bool checkOpp = isCheckOnMove(board, pieceToMove, from, to);
    setCheck(colorType(1 - getColor(pieceToMove)), checkOpp, board);
    promotion(board,getColor(pieceToMove), pieceToMove);
  }
  
  

  bool movePieceWithoutCheck(ChessPiece * pieceToMove, Cell to, ChessBoard* chessboard)
  {
    Cell from = getPosition(pieceToMove);
    removePiece(to,chessboard); // Hvis Motstanderns brikke blir tatt

    board[from.rowum][from.colum] = 0;
    board[to.rowum][to.colum] = pieceToMove;//reassign the pointers
    setPosition(to, pieceToMove);
    return true;//maybe change to void...
  }
  void rearrange(ChessBoard* chessboard, int emptyspot,ChessPiece** ownPieces)//not tested
  {
  colorType color= getColor(ownPieces[emptyspot]);
  int i=emptyspot;
  while(i<(((*chessboard).pieceslength[getColor(ownPieces[i])])-1))
  {
  ownPieces[i]=ownPieces[i+1];
  i++;
  }
  ((*chessboard).pieceslength[color])--;//decrement length of number of pieces
  }
  void removePiece(Cell pos, ChessBoard* chessboard)
  {
    ChessPiece * piece = getPiece(pos.colum, pos.rowum);
    if (piece == 0)
      return;

    board[pos.rowum][pos.colum] = 0;
    //piecesCaptured[getColor(piece)].push_back(piece);    
   (*chessboard).piecesCaptured[getColor(piece)][((*chessboard).piecescapturedlength[getColor(piece)])++]=piece;

    // TODO: Optimaliser dette.
    ChessPiece** ownPieces = getPieces(getColor(piece),chessboard);//return reference to piecevector. maybe remove...
    //std::vector<ChessPiece*>::iterator it = ownPieces.begin();
    int i=0;
    //for (; it != ownPieces.end(); it++) {
    while(i<(*chessboard).pieceslength[getColor(piece)]){
      if(piece == ownPieces[i]) {//check this, i think this should be matching addreses
        //ownPieces.erase(it);//removes the pointer only i think
        //free(ownPieces[i]);// no free, only decrement

         rearrange(chessboard,i,ownPieces);//there is a hole in the array that needs to be rearranged
        //((*chessboard).pieceslength[getColor(piece)])--;// this does not work, we have to rearrange array
        //decrement length;
        
        return;
      }
      i++;
    }
  }
  


