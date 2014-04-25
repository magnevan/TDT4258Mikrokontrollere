// Kontrollert av eirik flogard

#ifndef CHESS_VIEW_TERMINAL_H_
#define CHESS_VIEW_TERMINAL_H_

#include "chess_view.h"
#include "screen.h"



ChessView* ChessViewTerm(ChessGame* gameref);


void initializeRound(short* map, int fd); // initalize windows for new rounds

// Viser brettets tilstand på skjermen.
void printBoard(ChessBoard* board); //remove&change

// Viser mulige trekk.
void showValidMoves(Cell* moves, int size); //needed, change

// Ber brukeren velge en celle som brikken skal flyttes til
Cell* getCellFromPlayer(char* msg, bool pieceChosen, ChessView* view, Player* player, ChessBoard* board,Cell* cellFrom);

// Gir beskjed at denne cellen ikke kan velges.
void invalidCell(char* msg, Cell* cell);

void pieceMoved(Player* player, Cell* from, Cell* to);

// Printer meldinger på skjermen
void printMsg(char* msg);
void printErrorMsg(char* err);

Cell* askPlayerForACell(bool pieceChosen,Player* player, ChessBoard* board,Cell* cellFrom);

char* pieceToString(pieceType type, colorType color, short* map, int fd,int col, int row);



#endif
