// Kontrollert av eirik flogard


#include <string.h>
#include "chess_view_terminal.h"
ChessView* ChessViewTerm(ChessGame* gameref)
{
    return chessview1(gameref);

}


void initializeRound(short* map, int fd)
{
    ChessPiece* piece;
    pieceType type;
    colorType color;

    printf("Starting a new game of chess \n");

    screenclear( map, fd);
    drawboard(map, fd);
    //draw pieces
    int row=7;
    while(row>=0)
    {
        int col=0;
        while(col<8)//this will print the board itself
        {
            piece = getPiece(col, row);
            type = piece != 0 ? getType(piece) : EMPTY;
            color = (piece != 0 ? getColor(piece) : BLACK);
            printpiece(map, fd, type, color, col, row);
            col++;
        }
        row--;
    }
    munmap(map,FILESIZE);
    close(fd);

}

void printBoard(ChessBoard* board)//this is the method used for displaying
{   

    //put this map somewhere else. inefficient

    ChessPiece* piece;
    pieceType type;
    colorType color;
    int lightBackground = 1;

    int i, j, col, row;
    int tableStart = 2; // Starten av brettet


    i=0;
    while(i<= tableStart)
    {
        printf("-");
        i++;
    }

    i=0;
    while(i<8)
    {
        printf( "----");
        i++;
    }

    printf("\n");

    i=1;
    while(i<tableStart)
    {
        printf(" ");
        i++;
    }

    char letter = 'a';
    i=0;
    while(i<8)
    {
        printf("  ");
        printf("%c", letter);
        letter++;
        i++;
    }

    printf("\n");

    i=0;
    while(i<tableStart)
    {
        printf(" ");
        i++;
    }

    i=0;
    while(i<8)
    {
        printf(" ---");
        i++;
    }


    row=7;
    while(row>=0)
    {
        lightBackground = (row % 2 != 0);
        printf("\n");
        printf("%d",(row+1));
        j=1;
        while(j< tableStart)
        {
            printf(" ");
            j++;
        }
        printf("|");
        col=0;
        while(col<8)//this will print the board itself
        {
            piece = getPiece(col, row);
            type = piece != 0 ? getType(piece) : EMPTY;
            color = (piece != 0 ? getColor(piece) : BLACK);
            char* b_colorcode =(char*) (lightBackground ? "100" : "40");
            printf("\033[97;");
            printf("%s", b_colorcode);
            printf("m ");
            printf("%s",pieceToString(type, color,NULL,0,col,row));
            printf(" \033[0m|");
            if(lightBackground==1)
                lightBackground = 0;
            else lightBackground=1;
            col++;
        }
        row--;
    }
    printf("\n");
    i=0;
    while(i<tableStart)
    {
        printf(" ");
        i++;
    }

    i=0;
    while(i<8)
    {
        printf(" ---");
        i++;
    }
    printf("\n");

    i=0;
    while(i<= tableStart)
    {
        printf("-");
        i++;
    }

    i=0;
    while(i<8)
    {
        printf("----");
        i++;
    }

    printf("\n");

}

void showValidMoves(Cell* moves, int size)
{
    if (size == 0) {
        printf("No moves are possible with that chess piece.\n");
        return;
    }

    Cell cell;
    printf("Valid moves:");
    int i=0;

    while(i<size){

        printf(" %c",(moves[i].colum + 65) );
        printf("%d", (moves[i].rowum + 1));
        i++;
    }
    printf("\n");
}


Cell* getCellFromPlayer(char* msg, bool pieceChosen, ChessView* view, Player* player, ChessBoard* board,Cell* cellFrom)
{
    printMsg(msg);

    return askPlayerForACell(pieceChosen, player, board,cellFrom);
}

void invalidCell(char* msg, Cell* cell)
{

    printf("%c", ((*cell).colum + 65));
    printf("%d", ((*cell).rowum + 1 ));
    printf(": ");
    printf("%s", msg);

}

void pieceMoved(Player* player, Cell* from, Cell* to)
{
    int fd = open(FILEPATH, O_RDWR);
    if (fd == -1) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }
    short* map = mmap(0, FILESIZE, PROT_WRITE, MAP_SHARED, fd, 0);

    ChessPiece* piece = getPiece((*to).colum, (*to).rowum);
    pieceType type = piece != 0 ? getType(piece) : EMPTY;
    colorType color = (piece != 0 ? getColor(piece) : BLACK);
    squareclear(map,fd,(*from).colum, (*from).rowum);
    printf("%s", getName(player));
    printf(" moved a piece: ");
    printf("%c", ((*from).colum + 65));
    printf("%d", ((*from).rowum + 1));
    printf(" to ");
    printf("%c", ((*to).colum + 65));
    printf("%d", ((*to).rowum + 1));
    printf("\n");

    printpiece(map, fd, type, color, to->colum, to->rowum);

    munmap(map,FILESIZE);
    close(fd);
}

void printMsg(char* msg)
{

    printf("%s", msg);
}

void printErrorMsg(char* err)
{
    printf("%s", err);
}

Cell* askPlayerForACell(bool pieceChosen,Player* player, ChessBoard* board,Cell* cellFrom)//Dette er metoden som må endres
{

    char *s=(char*) malloc(sizeof(char)*100);
    ChessPiece** pieces;
    ChessPiece* piece;
    char counter=0;
    int col = 0, row = 0;
    int input;

    int fd = open(FILEPATH, O_RDWR);
    if (fd == -1) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }
    short* map = mmap(0, FILESIZE, PROT_WRITE, MAP_SHARED, fd, 0);

    while (true) {


        if(!pieceChosen)
        {
            printf("Scroll through pieces by writing 1 and -1. Your king is the currently selected piece. Write 8 to confirm a selection. ");//change to suitable buttons
            pieces=getPieces(getPlayerColor(player),board);
            while(true)
            {
                while(true)
                {
                    pause();
                    input = getLastButtonPressed();
                    if (input != -1) break;
                }

                if(input == 1 &&counter>0)//replace this with buttoncheck
                    counter--;
                else if(input == 3 && counter<((*board).pieceslength[getPlayerColor(player)]-1))
                    counter++;
                else
                    printf("Invalid input. Write 1 or -1 to choose a piece\n");
                pieceType type = pieces[counter] != 0 ? getType(pieces[counter]) : EMPTY;

                printmarker(map, fd, 0, col, row);

                col = getPosition(pieces[counter]).colum;
                row = getPosition(pieces[counter]).rowum;
                printf("%s" ,pieceToString(type, getPlayerColor(player), NULL,0,col, row));
                printf(" currently at");
                printf(" %c",(col + 65) );
                printf("%d", (row + 1));
                printf(" is selected\n");

                printmarker(map, fd, 1, col, row);

                if( input == 8)
                {
                    printmarker(map, fd, 0, col, row);
                    break;
                }
            }

        }
        else
        {
            printf("Scroll through all possile moves of your selected piece by writing 1 and -1. Write 8 to confirm a selection. Write 9 to abort selection\n ");//change to suitable buttons
            piece = getPiece((*cellFrom).colum, (*cellFrom).rowum);
            int length=0;
            Cell* moves = getPossibleMoves(board,piece,&length);
            col = moves[counter].colum;
            row = moves[counter].rowum;
            printmarker(map, fd, 1, col, row);
            while(true)
            {
                while(true)
                {
                    pause();
                    input = getLastButtonPressed();
                    if (input != -1) break;
                }

                if(input == 1 && counter>0)//replace this with buttoncheck
                    counter--;
                else if(input == 3&&counter<(length-1))//replace input1 check with buttoncheck
                    counter++;
                else
                    printf("Invalid selection. Write 1 or -1 to choose a where to move\n");
                printf("write 9 to abort to chose new piece. Write 8 to confirm selection\n");

                printmarker(map, fd, 0, col, row);

                pieceType type = piece != 0 ? getType(piece) : EMPTY;
                col = moves[counter].colum;
                row = moves[counter].rowum;
                printf("%s" ,pieceToString(type, getPlayerColor(player), NULL,0,col, row));
                printf("s possible move to ");
                printf(" %c",(moves[counter].colum + 65) );
                printf("%d", (moves[counter].rowum + 1));
                printf(" is selected\n");

                printmarker(map, fd, 1, col, row);

                if(input == 8)//7 is abort and 8 is ok, change this to test the button vector
                {
                    printmarker(map,fd, 0, col, row);
                    break;
                }
                else if(input == 7)
                {
                    printmarker(map,fd, 0, col, row);
                    row=-1;
                    col=-1;
                    break;
                }



            }

        }
        munmap(map, FILESIZE);
        close(fd);

        Cell* cell2=(Cell*) malloc(sizeof(Cell));
        (*cell2).rowum=row;
        (*cell2).colum=col;
        free(s);
        return cell2;
    }
    return NULL;
}

char* pieceToString(pieceType type, colorType color, short* map, int fd,int col, int row)
{

    switch(type) {
        case EMPTY:
            return " ";
        case PAWN:

            return (color == BLACK ? "♙" : "♟");
        case ROOK:

            return (color == BLACK ? "♖" : "♜");
        case BISHOP:

            return (color == BLACK ? "♗" : "♝");
        case KNIGHT:

            return (color == BLACK ? "♘" : "♞");
        case QUEEN:

            return (color == BLACK ? "♕" : "♛");
        default:

            return (color == BLACK ? "♔" : "♚");
    }
}
