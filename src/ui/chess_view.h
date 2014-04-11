// Kontrollert av Eirik Flogard

#ifndef CHESS_VIEW_H_
#define CHESS_VIEW_H_

#include "../chess_game.h"
#include <string>


  struct ChessView
  {
    ChessGame* game;  // Referanse til game-objektet (kontroller)
    };
  //public:
    ChessView* chessview1(ChessGame* gameref);

   /* virtual std::string getName() = 0; // Ber spilleren om å oppgi et navn.

    // Skriver ut listen over alle spillere
    virtual void printPlayers(Player* players) = 0;

    virtual bool getNewRound() = 0; // Spør om spilleren vil spille mer.
    virtual void initializeRound() = 0; // Gjør vinduet klar for ny runde.

    // Viser brettets tilstand på skjermen.
    virtual void printBoard(ChessBoard & board) = 0;

    // Viser mulige trekk.
    virtual void showValidMoves(std::vector<Cell> moves) = 0; 

    // Ber brukeren velge en celle med en brikke i.    
    //virtual Cell getCellWithPieceFromPlayer(std::string msg) = 0;

    // Ber brukeren velge en celle som brikken skal flyttes til.
    virtual Cell getCellFromPlayer(std::string msg, bool pieceChosen) = 0;

    // Gir beskjed at denne cellen ikke kan velges.
    virtual void invalidCell(std::string msg, Cell cell) = 0;

    virtual void pieceMoved(Player & player, Cell from, Cell to) = 0;

    // Printer melding.
    virtual void printMsg(std::string msg) = 0;
    // Printer feilmelding.
    virtual void printErrorMsg(std::string err) = 0;
  */
//}

#endif
