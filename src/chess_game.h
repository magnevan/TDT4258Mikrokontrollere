// Kontrollert av eirik flogard

#ifndef CHESS_GAME_H_
#define CHESS_GAME_H_

#include "chess_board.h"
#include "chess_player.h"


  typedef enum{TERM, GUI} viewType;
  //typedef enum { false, true } bool;
  class ChessViewTerm;
  class ChessView;
  //class Player;

  struct ChessGame
  {
    // Model
    Player* players[2];

    // View
    ChessView * view;
    };
 // public:
   ChessGame* chessgame1(viewType UItype, playerType player1_type,
	      playerType player2_type);
    //~ChessGame();

    void startGame();
    void newRound(bool slowSpeed,ChessGame* chessgame);
    void movePiece(Player* player, ChessBoard* board);
    bool gameIsFinished(Player* lastPlayer, ChessBoard* board);
  \


#endif