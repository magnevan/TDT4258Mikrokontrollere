// Kontrollert av eirik flogard


#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/fb.h>
#include <fcntl.h>
#include "chess_view_terminal.h"
#define FILEPATH "/dev/fb0"
#define FILESIZE (320*240)

ChessView* ChessViewTerm(ChessGame* gameref)
{
return chessview1(gameref);

}


  void initializeRound()
  {
    ChessPiece* piece;
    pieceType type;
    colorType color;
    int fd = open(FILEPATH, O_RDWR);
    short* map = mmap(0, FILESIZE, PROT_WRITE, MAP_SHARED, fd, 0);
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
	drawpieces(type, color,map,fd,col,row);
    col++;
    }
    row--;
    }
munmap(map,FILESIZE);
	close(fd);

  }

  void printBoard(ChessBoard* board)//this is the method used for displaying
  {   
	 int fd = open(FILEPATH, O_RDWR);
  short* map = mmap(0, FILESIZE, PROT_WRITE, MAP_SHARED, fd, 0);   
    if (fd == -1) {
    perror("Error opening file for reading");
    exit(EXIT_FAILURE);
    }
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
     printf("%s",pieceToString(type, color,map,fd,col,row));
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
munmap(map,FILESIZE);
close(fd);
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


  Cell* getCellFromPlayer(char* msg, bool pieceChosen, ChessView* view)
  {
    printMsg(msg);
    
    return askPlayerForACell(pieceChosen);
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
    switch(type) {
    case EMPTY:
      return;
    case PAWN:
      printpiecePawn(map,fd,color,(*to).colum,(*to).rowum);
      break;
    case ROOK:
      printpieceRook(map,fd,color,(*to).colum,(*to).rowum);
      break;
    case BISHOP:
      printpieceBishop(map,fd,color,(*to).colum,(*to).rowum);
      break;
    case KNIGHT:
      printpieceKnight(map,fd,color,(*to).colum,(*to).rowum);
      break;
    case QUEEN:
      printpieceQueen(map,fd,color,(*to).colum,(*to).rowum);
      break ;
    default:
      printpieceKing(map,fd,color,(*to).colum,(*to).rowum);
      break ;
    }
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

  Cell* askPlayerForACell(bool pieceChosen)//Dette er metoden som må endres
  {

        char *s=(char*) malloc(sizeof(char)*100);


    int col, row;
    while (true) {

      printf("Enter square number (e.g. A7, G4 etc.");
      if(pieceChosen)
      printf(" Leave prompt empty to abort.");
      printf("): \0");

      bool correct = false;
      while (true) {
      
          scanf("%s",s);
        if (strlen(s) == 2) {
          char colInput = s[0];
          char rowInput = s[1];
          if (colInput < 'A' || colInput > 'h' ||
              (colInput > 'H' && colInput < 'a')) {
            printf("Invalid column. Should be a character between a and h.\n");
          } else if (rowInput < 49 || rowInput > 56) {
            printf("Invalid row. Should be an integer between 1 and 8.\n");
          } else {
            col = colInput - (colInput <= 'H' ? 65 : 97);
            row = rowInput - 49;
            break;
          }
        } 
        else if (pieceChosen && strlen(s) ==0)
        {
        Cell* cell=(Cell*) malloc(sizeof(Cell));
        (*cell).rowum=-1;
        (*cell).colum=-1;
        free(s);
          return cell; // Ugyldig celle, avslutter valget.
        }
        printf("Please choose a valid square\n");
        if(pieceChosen)
         printf(" (Leave prompt empty to abort.): \n");   
         else
         printf(": \n");
      }
              Cell* cell2=(Cell*) malloc(sizeof(Cell));
                      (*cell2).rowum=row;
        (*cell2).colum=col;
        free(s);
      return cell2;
    }
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

void drawpieces(pieceType type, colorType color, short* map, int fd,int col, int row)
{
    switch(type) {
    case EMPTY: //no output for empty piece
      return;
    case PAWN:
      printpiecePawn(map,fd,color,col,row);
      return ;
    case ROOK:
      printpieceRook(map,fd,color,col,row);
      return;
    case BISHOP:
      printpieceBishop(map,fd,color,col,row);
      return;
    case KNIGHT:
      printpieceKnight(map,fd,color,col,row);
      return;
    case QUEEN:
      printpieceQueen(map,fd,color,col,row);
      return;
    default:
      printpieceKing(map,fd,color,col,row);
      return;
    }

}

