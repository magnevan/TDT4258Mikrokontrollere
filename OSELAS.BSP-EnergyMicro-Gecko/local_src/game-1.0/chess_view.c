// Kontrollert av eirik Flogard

#include <string.h>

#include "chess_view.h"


ChessView* chessview1(ChessGame* gameref) 
{
    ChessView* chessview=(ChessView*) malloc(sizeof(ChessView));
    (*chessview).game=gameref;
    return chessview;
}

