//Kontrollert av Eirik Flogard

#ifndef CHESS_BOARD_H_
#define CHESS_BOARD_H_



//#include "chess_cell.h"
#include "chess_piece.h"


// Brikkene på brettet.
static ChessPiece *** board;//a predeclaration of the board

/* 
 * En vector av brikkepekere til hver av spillerne. De er sortert etter
 * poengsum i synkende rekkefølge.
 */
typedef struct ChessBoard ChessBoard;
struct ChessBoard {
    ChessPiece** pieces[2];
    ChessPiece** piecesCaptured[2];
    int piecescapturedlength[2];//må ha farge også
    int pieceslength[2];//må ha farge også
    int turns; // Totalt antall trekk utført

    bool check[2]; // Sannhetsverdi på om det er sjakk for spilleren.
};
void initializeBoard(ChessBoard* chessboard);


/* 
 * Returnerer en peker til brikken som ligger i den ruten som sendes som
 * argument. Hvis det ikke finnes noen brikker der, returneres en null-peker.
 */
ChessBoard* Chessboard1();
ChessPiece* getPiece(int col, int row);
ChessPiece*** getallPieces();//returnerer den statiske "boardpekeren" ovenfor. Brukes primært for free().

/* 
 * Returnerer en vector av brikkepekere for en spiller som har den fargen på
 * brikken som sendes som argument. Brikkene er stortert etter poengsum i
 * synkende rekkefølge.
 */
ChessPiece** getPieces(colorType color, ChessBoard* chessboard);
ChessPiece** getCapturedPieces(colorType color, ChessBoard* chessboard);

bool movePieceWithoutCheck(ChessPiece * pieceToMove, Cell to, ChessBoard* chessboard);
void  removePiece(Cell pos, ChessBoard* chessboard);

int getTurns(ChessBoard* chessboard);
void placeBackLastCapturedPiece(colorType color, ChessBoard* chessboard);
/* 
 * Returnerer sannhetsverdien på om den spilleren som har sin tur å spille
 * er i sjakk.
 */
bool isCheck2(colorType color,ChessBoard* chessboard);

bool setCheck(colorType color, bool checkValue,ChessBoard* chessboard);

void movePlayerPieceTo(Cell from, Cell to, ChessBoard* board);
void setPiece(pieceType ptype, colorType pcolor, Cell startpos, ChessBoard* chessboard);


#endif
