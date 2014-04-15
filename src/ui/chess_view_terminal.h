// Kontrollert av eirik flogard

#ifndef CHESS_VIEW_TERMINAL_H_
#define CHESS_VIEW_TERMINAL_H_

#include "chess_view.h"




  ChessView*  ChessViewTerm(ChessGame* gameref);
    
    // Ber spilleren om å oppgi et navn.


    // Skriver ut listen over alle spillere
   

    // Spør om spilleren vil spille mer.

   void initializeRound(); // Gjør vinduet klar for ny runde.

    // Viser brettets tilstand på skjermen.
  void printBoard(ChessBoard* board); //remove&change

    // Viser mulige trekk.
   void showValidMoves(Cell* moves, int size); //needed, change

    // Ber brukeren velge en celle med en brikke i.    
    //virtual Cell getCellWithPieceFromPlayer(std::string msg);

    // Ber brukeren velge en celle som brikken skal flyttes til
    Cell* getCellFromPlayer(char* msg, bool pieceChosen, ChessView* view);

    // Gir beskjed at denne cellen ikke kan velges.
    void invalidCell(char* msg, Cell* cell);

    void pieceMoved(Player* player, Cell* from, Cell* to);

    // Printer meldinger på skjermen
    void printMsg(char* msg);
    void printErrorMsg(char* err);

    Cell* askPlayerForACell(bool pieceChosen);

   const char* pieceToString(pieceType type, colorType color);



#endif
