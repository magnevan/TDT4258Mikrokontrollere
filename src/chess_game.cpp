// Kontrollert av eirik flogard

#include "ui/chess_view_terminal.h"
#include "chess_game.h"
#include "chess_rules.h"


#include <string>

//#include <iostream>


ChessGame* chessgame1(viewType UIType, 
                       playerType player1_type, playerType player2_type)
  {
  ChessGame* chessgame=(ChessGame*) malloc(sizeof(ChessGame));
  
    // Oppretter view-objektet
    //view = new ChessViewTerm(this); må finne annen løsning

    // Opprettet spillere
    //players = malloc(2*sizeof(*players));//new Player[2];

  (*chessgame).players[0] = Player1("Player 1 \0", player1_type, BLACK);

    //std::string nameinput = view->getName();
   // std::string name;//change?
   
      //name = "Player 2";

    (*chessgame). players[1] = Player1("Player 2", player2_type, WHITE);

    (*chessgame).view=ChessViewTerm(chessgame);
    //view->printPlayers(players); dont needthis anyways yet
  }


  void startGame(ChessGame* chessgame)
  {

    while (true) {
      newRound(false, chessgame);//allways start new round
      //if (!view->getNewRound())
      //  break;
    }
  }

  void newRound(bool slowSpeed,ChessGame* chessgame)
  {
    // Oppretter brettet
    ChessBoard * board = Chessboard1();//setup board and initialize
    //I need to make a struct containing initializeable variables of chessboard?
    initializeRound();
    //view->printBoard(*board); we must come up with a way to display the board
    int currentPlayer = 1;

    while (true) {
      movePiece((*chessgame).players[currentPlayer], board,(*chessgame).view);

      printBoard(board);
      if (gameIsFinished((*chessgame).players[currentPlayer], board,(*chessgame).view))
        break;
      currentPlayer = 1 - currentPlayer;

      if (isCheck(getColor((*chessgame).players[currentPlayer]),board)) {
        //printMsg("*" + getName((*chessgame).players[currentPlayer]) +" is in check.*",view);
        printMsg(getName((*chessgame).players[currentPlayer]));
      }
             
    }
     //rest of the method frees everything allocated in board
     ChessPiece*** deleteboard= getallPieces();
     int row=0;
     int i=0;
     int j=0;
     while(j<2)
     {
     while(i<(*board).pieceslength[j])
     {
     free((*board).pieces[j][i]);
     i++;
     }
     free((*board).pieces[j]);
     j++;
     }
     
     i=0;
     j=0;
        while(j<2)
     {
     while(i<(*board).piecescapturedlength[j])
     {
     free((*board).piecesCaptured[j][i]);
     i++;
     }
     free((*board).piecesCaptured[j]);
     j++;
     }
     while(row<8)
     {
 
     free(deleteboard[row]);

     row++;

     }
     free(deleteboard);
    free(board);
  }

  void movePiece(Player* player, ChessBoard* board, ChessView* view)//vi må fikse denne
  {
    Cell* cellFrom;
    Cell* cellTo;
    ChessPiece * piece;
    bool pieceNotMoved = true;
    if (getType(player) != BOT) {
      char* msg = "It's your turn. Please choose a chess piece.";
      while (pieceNotMoved) {
        while (true) {
          cellFrom = getCellFromPlayer(msg, false,view);//reconfigure this to the gameboard
          piece = getPiece((*cellFrom).colum, (*cellFrom).rowum);//board
          if (piece == 0) {
            invalidCell("Not a chess piece!", cellFrom);
            msg = "Please choose a chess piece from the board!";
          } else if (getColor(piece) != getColor(player)) {//overloaded?
            invalidCell("That is one of the opponent's chess pieces!",
                              cellFrom);
            msg = "Please choose one of you own chess pieces.";
          } else {
          int counter=0;
            Cell* moves = getPossibleMoves(board,piece,&counter);//getpossiblemoves returnerer en vektor(array) med alle mulige moves. Gamepaden kan brukes til å velge move
            showValidMoves(moves,counter);
            //if (moves.size() > 0)
            if (counter> 0)
            {
            
            free(moves);
              break;
              }
              free(moves);
            msg = "Please choose a different chess piece.";
          }
        }

        msg = "Please choose a valid square to move the piece to.";

        while (true) {//will continue to prompt for moves unto a valid is selected
          cellTo = getCellFromPlayer(msg, true,view);
          if ((*cellTo).colum < 0 || (*cellTo).rowum < 0) {
            msg = "Aborted. Please choose a chess piece.";

            break;

          }
          // checks if move is valid before moving
          if (validMove(board, (*cellTo),piece)) {
           movePlayerPieceTo((*cellFrom), (*cellTo), board);

            pieceNotMoved = false;
            break;
          }
          else
          {
            invalidCell("Invalid move.", cellTo);

            }
        }

      }
    }  else {
      printf("there is currently only one type of player");
      return;
    }

    pieceMoved(player, cellFrom, cellTo);
          free(cellFrom);
          free(cellTo);
  } // end of method movePiece(Player & player, ChessBoard * board)

  bool gameIsFinished(Player* lastPlayer, ChessBoard* board, ChessView* view)
  {
    if (win(board, getColor(lastPlayer))) {
      //printMsg("CHECK MATE. " + getName(lastPlayer) + " won.", view);
      printMsg("CHECK MATE. ");
      printMsg(getName(lastPlayer) );
      printMsg( " won.");
      
      return true;
    } else if(stalemate(board, getColor(lastPlayer))) {
      printMsg("STALEMATE. Game is a draw.");
      return true;
    } else if (tie(board)) {
      printMsg("DRAW. Game is over.");
      return true;
    }

    return false;
  }

