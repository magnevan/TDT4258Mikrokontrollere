// Kontrollert av eirik flogard

#include "chess_view_terminal.h"
#include "chess_game.h"
#include "chess_rules.h"


#include <string.h>



ChessGame* chessgame1(viewType UIType, 
        playerType player1_type, playerType player2_type)
{
    ChessGame* chessgame=(ChessGame*) malloc(sizeof(ChessGame));

    // Oppretter view-objektet

    // Opprettet spillere


    (*chessgame).players[0] = Player1("Player 1", player1_type, BLACK);



    (*chessgame). players[1] = Player1("Player 2", player2_type, WHITE);
    //NB playernames are not yet initialized
    (*chessgame).view=ChessViewTerm(chessgame);
    return chessgame;
}


void startGame(ChessGame* chessgame)
{

    //while (true) {
    newRound(false, chessgame);

    //}
}

//slowspeed is for expandable feature if we want to use graphics or similar.
void newRound(bool slowSpeed,ChessGame* chessgame)
{
    // Oppretter brettet

    //I need to make a struct containing initializeable variables of chessboard?


    int fd = open(FILEPATH, O_RDWR);
    if (fd == -1) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }
    ChessBoard * board = Chessboard1();//setup board and initialize
    short* map = mmap(0, FILESIZE, PROT_WRITE, MAP_SHARED, fd, 0);
    initializeRound(map,fd);
    int currentPlayer = 1;
    printBoard(board);
    while (true) {
        movePiece((*chessgame).players[currentPlayer], board,(*chessgame).view, map, fd);
        printBoard(board);
        if (gameIsFinished((*chessgame).players[currentPlayer], board,(*chessgame).view))
            break;
        currentPlayer = 1 - currentPlayer;
        if (isCheck2(getPlayerColor((*chessgame).players[currentPlayer]),board)) {

            printMsg(getName((*chessgame).players[currentPlayer]));
            printMsg("Is in check\n");
        }

    }
    //rest of the method frees everything allocated in board
    ChessPiece*** deleteboard= getallPieces();
    int row=0;
    int i=0;
    int j=0;
    while(j<2)
    {
        while(i<(*board).pieceslength[j])
        {
            free((*board).pieces[j][i]);
            i++;
        }
        free((*board).pieces[j]);
        j++;
    }

    i=0;
    j=0;
    while(j<2)
    {
        while(i<(*board).piecescapturedlength[j])
        {
            free((*board).piecesCaptured[j][i]);
            i++;
        }
        free((*board).piecesCaptured[j]);
        j++;
    }
    while(row<8)
    {

        free(deleteboard[row]);

        row++;

    }
    free(deleteboard);
    free(board);
    munmap(map,FILESIZE);
    close(fd);
}

void movePiece(Player* player, ChessBoard* board, ChessView* view, short* map, int fd)
{
    Cell* cellFrom;
    Cell* cellTo;
    ChessPiece * piece;
    bool pieceNotMoved = true;

    getPlayerType(player);
    if (getPlayerType(player) != BOT) {
        char* msg = "It's your turn. Please choose a chess piece.\n";
        while (pieceNotMoved) {
            while (true) {
                cellFrom = getCellFromPlayer(msg, false,view, player, board,NULL);
                piece = getPiece((*cellFrom).colum, (*cellFrom).rowum);// method found on board
                if (piece == 0) {
                    invalidCell("Not a chess piece!", cellFrom);
                    msg = "Please choose a chess piece from the board!\n";
                } else if (getColor(piece) != getPlayerColor(player)) {
                    invalidCell("That is one of the opponent's chess pieces!\n",
                            cellFrom);
                    msg = "Please choose one of you own chess pieces.\n";
                } else {
                    int counter=0;
                    Cell* moves = getPossibleMoves(board,piece,&counter);
                    showValidMoves(moves,counter);
                    if (counter> 0)
                    {

                        free(moves);
                        break;
                    }
                    free(moves);
                    msg = "Please choose a different chess piece.\n";
                }
            }

            msg = "Please choose a valid square to move the piece to.\n";

            while (true) {//will continue to prompt for moves unto a valid is selected
                cellTo = getCellFromPlayer(msg, true,view,player,board,cellFrom);
                if ((*cellTo).colum < 0 || (*cellTo).rowum < 0) {
                    msg = "Aborted. Please choose a chess piece.\n";

                    break;

                }
                // checks if move is valid before moving
		bool bigcastle=false;
		bool smallcastle=false;
                if (validMove(board, (*cellTo),piece)) {
		   if((*cellTo).rowum==(*cellFrom).rowum && (*cellTo).colum==((*cellFrom).colum+2)) {
			//liten rokkade,ischeckonmove

			if(smallCastling(board,piece,(*cellFrom))) {
				smallcastle=true;
				drawboard(map,fd);

			}
		   
		    } else if((*cellTo).rowum==(*cellFrom).rowum&&(*cellTo).colum==((*cellFrom).colum-3)) {
			//ischeckonmove

			if(bigCastling(board,piece,(*cellFrom)))
			{
			bigcastle=true;
			drawboard(map, fd);

			}
		    }
                    movePlayerPieceTo((*cellFrom), (*cellTo), board);
		if(bigcastle || smallcastle)
		{
			int rowa=7;
			    while(rowa>=0)
			    {
				int cola=0;
				while(cola<8)//this will print the board itself
				{
				    piece = getPiece(cola, rowa);
				    pieceType type = piece != 0 ? getType(piece) : EMPTY;
				   colorType color = (piece != 0 ? getColor(piece) : BLACK);
				    printpiece(map, fd, type, color, cola, rowa);
				    cola++;
				}
				rowa--;
			    }
		}
		    bigcastle=false;
		    smallcastle=false;
                    (*piece).moved++;
                    pieceNotMoved = false;
                    break;
                }
                else
                {
                    invalidCell("Invalid move.", cellTo);

                }
            }

        }
    }  else {
        printf("there is currently only one type of player\n");
        return;
    }

    pieceMoved(player, cellFrom, cellTo, board);
//this is a quickfix for a displaybug on efm33gg related to castling
 
    free(cellFrom);
    free(cellTo);
} // end of method movePiece(Player & player, ChessBoard * board)

bool gameIsFinished(Player* lastPlayer, ChessBoard* board, ChessView* view)
{
    if (win(board, getPlayerColor(lastPlayer))) {
        printMsg("CHECK MATE. ");
        printMsg(getName(lastPlayer) );
        printMsg( " won.\n");

        return true;
    } else if(stalemate(board, getPlayerColor(lastPlayer))) {
        printMsg("STALEMATE. Game is a draw.\n");
        return true;
    } else if (tie(board)) {
        printMsg("DRAW. Game is over.\n");
        return true;
    }

    return false;
}

