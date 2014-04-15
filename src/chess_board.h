//Kontrollert av Eirik Flogard

#ifndef CHESS_BOARD_H_
#define CHESS_BOARD_H_

#include <vector>

//#include "chess_cell.h"
#include "chess_piece.h"


    // Brikkene på brettet.
    static ChessPiece *** board;//the name "board" need to be static since the name is reused as arguments
//typedef enum { false, true } bool;
    /* 
     * En vector av brikkepekere til hver av spillerne. De er sortert etter
     * poengsum i synkende rekkefølge.
     */
   struct ChessBoard{
    ChessPiece** pieces[2];
    ChessPiece** piecesCaptured[2];
    int piecescapturedlength[2];//må ha farge også
    int pieceslength[2];//må ha farge også
    int turns; // Totalt antall trekk

    bool check[2]; // Sannhetsverdi på om det er sjakk for spilleren.
};
    void initializeBoard(ChessBoard* chessboard);


 //public:
   // ChessBoard();
    //~ChessBoard();

    /* 
     * Returnerer en peker til brikken som ligger i den ruten som sendes som
     * argument. Hvis det ikke finnes noen brikker der, returneres en null-peker.
     */
       ChessBoard* Chessboard1();
    ChessPiece* getPiece(int col, int row);
    ChessPiece*** getallPieces();//returnerer den statiske "boardpekeren" ovenfor. Brukes primært for free().
    //void redoPromotion(Cell position,colorType color,ChessPiece* lastPiece);
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
    bool isCheck(colorType color,ChessBoard* chessboard);

    bool setCheck(colorType color, bool checkValue,ChessBoard* chessboard);

    // Sjekker brettet om motspillerern er i sjakk
    //bool isCheckOnNextMove(Cell from, Cell to); 

    /* 
     * Flytter brikken som ligger på posisjon "from" til den ruten som ligger på
     * posisjon "to". Det antas at trekket er lovlig. Denne metoden flytter ikke
     * brikken hvis spillet er i sjakk. Ingenting skjer hvis det ikke finnes en
     * brikke på rute "from".
     */
    //void movePieceTo(Cell from, Cell to);
    //void moveBackPieceTo(Cell from, Cell to);
    void movePlayerPieceTo(Cell from, Cell to, ChessBoard* board);
    void setPiece(pieceType ptype, colorType pcolor, Cell startpos, ChessBoard* chessboard);
   // void placeBackLastCapturedPiece(colorType color);
    /*
     * Fungerer på samme måte som movePieceTo()-metoden, men den sjekker ikke om
     * motstanderen er i sjakk etter trekket.  Den er ment for å brukes til å
     * flytte brikken etter et forsøk på å se om brikken kan fjerne sjakk
     * for sin egen konge. Hvis brikkens posisjon ikke stemmer med det som sendes
     * som argumentetvariablen "from", skjer det ingenting.
     */
    //void movePiece(ChessPiece * piece, Cell from, Cell to);

    /*
     * Lager en ny brikke og plaserer den i den posisjonen som sendes som
     * argument. Hvis det eksisterer en brikke der fra før av, slettes den.
     */
    //void placePiece(pieceType type, colorType color, Cell to);

    /* 
     * Sletter brikken fra brettet. Den vil også bli slettet fra minnet. Hvis
     * brikken må huskes, må du ta en kopi av den.
     */
  //  void deletePiece(ChessPiece * piece);


#endif
