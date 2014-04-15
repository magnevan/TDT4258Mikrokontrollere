// Kontrollert av Eirik Flogard

#ifndef CHESS_VIEW_H_
#define CHESS_VIEW_H_

#include "../chess_game.h"
#include <string>


  struct ChessView//struct designed for containing information about display. I currently not used for anything
  {
    ChessGame* game;  // Referanse til game-objektet (kontroller)
    };
  //public methods
    ChessView* chessview1(ChessGame* gameref);


#endif
