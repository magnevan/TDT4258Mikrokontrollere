// Kontrollert av eirik flogard

#ifndef CHESS_GAME_H_
#define CHESS_GAME_H_

#include "chess_board.h"
#include "chess_player.h"


typedef enum{TERM, GUI} viewType;

typedef struct ChessView ChessView;
struct ChessView;
typedef struct ChessGame ChessGame;
struct ChessGame
{
    // Model
    Player* players[2];

    // View
    ChessView * view;
};

ChessGame* chessgame1(viewType UItype, playerType player1_type,
        playerType player2_type);


/*the methods startgame and newround initializes the board and neccesary resources and starts a new round*/
void startGame(ChessGame* chessgame);
void newRound(bool slowSpeed,ChessGame* chessgame);
/* movePiece() is responcible for receiving input and execute moves. The method is constructed with as many sanity checks as possible to prevent any possible crash bugs 
   to occur. This means more energy use, but more stability. */
void movePiece(Player* player, ChessBoard* board, ChessView* view, short* map, int fd);
/*this method checks if the game is finished. THese methods can be found in the chessrules module*/
bool gameIsFinished(Player* lastPlayer, ChessBoard* board, ChessView* view);



#endif
