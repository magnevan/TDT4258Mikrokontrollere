// Kontrollert av eirik
#ifndef CHESS_RULES_H_
#define CHESS_RULES_H_


struct ChessBoard;


/*
 * Sjekker om kongen er i sjakk ved å sjekke i vertikalt (oppover eller
 * nedover) eller horisontalt retning (til høyre eller til venstre).
 */
bool isCheckStraight(ChessBoard* board, colorType kingColor,
        bool vertical, bool rightOrUp);

/*
 * Sjekker om kongen er i sjakk ved å sjekke i vertikalt (oppover eller
 * nedover) eller horisontalt retning (til høyre eller til venstre).
 */
bool isCheckDiagonal(ChessBoard* board, colorType kingColor,
        bool upwards, bool right);

/*
 * Sjekker om noen av motstanderns springere kan ta kongen med den fargen
 * som sendes som argument.
 */
bool isCheckKnight(ChessBoard* board,
        colorType kingColor);

//public:
// Sjekker om spilleren som nettopp gjorde et trekk vant.
bool win(ChessBoard* board, colorType lastColorMove);

/* 
 * Sjekker om spillet er i "stalemate". Dette regnes som et spesialtilfelle
 * av uavgjort.
 */
bool stalemate(ChessBoard* board, colorType lastColorMove);

/*
 * Sjekker om det er uavgjort. Altså sjekker om det finnes noen muligheter
 * for å vinne. Spillet er uavgjort hvis følgende brikker er igjen:
 * - Konge mot konge.
 * - Konge og løper mot konge.
 * - Konge og springer mot konge.
 * - Konge og løper mot konge og løper der løperne er på samme farge i
 *   brettet.
 */
bool tie(ChessBoard* board);

/* Sjekker om spilleren med den fargen som sendes som argument har noen
 * mulige trekk.
 */
bool hasMoves(ChessBoard* board, colorType color);

/*
 * Sjekker om neste trekk fører til at egen konge havner i sjakk. Hvis
 * brikken har allerede flyttet seg, sjekkes det om trekket førte til at
 * motstanderns konge havnet i sjakk.
 */
bool isCheckOnMove(ChessBoard* board,
        ChessPiece * pieceToMove, Cell from, Cell to);

/* 
 * Sjekker om kongen med den fargen som sendes som argument er i sjakk.
 * Denne metoden sjekker alle retninger og om motstanderens springer kan ta
 * kongen. Metoden bør ikke kalles, med mindre du ikke vet retningen som bør
 * sjekkes. Bruk da heller metodene isCheckStraight, isCheckDiagonal eller
 * isCheckKnight.
 */
bool isCheck(ChessBoard* board, colorType kingColor);


void promotion(ChessBoard* board,colorType color, ChessPiece* piece);


#endif
