// Kontrollert av eirik flogard

//#include <string>
//#include <iostream>
//#include <sstream>
//#include <limits>
//#include <stdio.h>
#include <string.h>
//#include "../chess_player.h"
#include "chess_view_terminal.h"
using namespace std;
ChessView*  ChessViewTerm(ChessGame* gameref)
{
return chessview1(gameref);

}



  void initializeRound()
  {
   printf("Starting a new game of chess \n");
  }

  void printBoard(ChessBoard* board)//this is the method used for displaying
  {

    ChessPiece* piece;
    pieceType type;
    colorType color;
    int lightBackground = 1;
    std::string colorcode;
    std::string b_colorcode;
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

    
    // TODO: Øverste rad må begynne fra 8
    row=7;
    while(row>=0)
    {
    lightBackground = (row % 2 != 0);
    printf("\n");
    printf("%d",(row+1));//this wont work prob
    j=1;
    while(j< tableStart)
    {
    printf(" ");
    j++;
    }
    printf("|");
    col=0;
    while(col<8)
    {
    piece = getPiece(col, row);//check htis
     type = piece != 0 ? getType(piece) : EMPTY;//check this
     color = (piece != 0 ? getColor(piece) : BLACK);//check this
      b_colorcode = (lightBackground ? "100" : "40");
      printf("\033[97;");
     // printf(b_colorcode);
      printf("m ");
     // printf(pieceToString(type, color));//check this too
     printf("%c",pieceToString(type, color));
      printf(" \033[0m|");
      if(lightBackground==1)
      lightBackground = 0;
      else lightBackground=1;
    col++;
    }
    row--;
    }
   /* for (row = 7; row >= 0; row--) {
      lightBackground = (row % 2 != 0);
      cout << "\n" << row + 1;
      for (j = 1; j < tableStart; j++)
        cout << " " ;
      cout << '|';
      for (col = 0; col < 8; col++) {
        piece = board.getPiece(col, row);
        type = piece != 0 ? piece->getType() : EMPTY;
        color = (piece != 0 ? piece->getColor() : BLACK);
        b_colorcode = (lightBackground ? "100" : "40");
        cout << "\033[97;" << b_colorcode << "m " << pieceToString(type, color)
             << " \033[0m|";
        lightBackground = !lightBackground;
      }
    }*/

    printf("\n");
    //cout << "\n";
    i=0;
    while(i<tableStart)
    {
    printf(" ");
    i++;
    }
       // for (i = 0; i < tableStart; i++)
      //cout << " ";
    i=0;
    while(i<8)
    {
    printf(" ---");
    i++;
    }
    printf("\n");
    

    //for (i = 0; i < 8; i++)
      //cout << " ---";
    //cout << endl;

    /*cout << "K: King - Q: Queen - R: Rook - B: Bishop - N: Knight - P: Pawn"
      << endl;*/
   /* cout << "King: ♚/♔, Queen: ♛/♕, Rook: ♜/♖, Bishop: ♝/♗, "
         << "Knight: ♞/♘, Pawn: ♟/♙."
         << endl;*/

         i=0;
         while(i<= tableStart)
         {
         printf("-");
         i++;
         }
   // for (i = 0; i <= tableStart; i++)
     // cout << "-";
     i=0;
     while(i<8)
     {
     printf("----");
     i++;
     }
    //for (i = 0; i < 8; i++)
      //cout << "----";
      printf("\n");
    //cout << endl;
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

  /*Cell ChessViewTerm::getCellWithPieceFromPlayer(ChessBoard * board,
    Player * pl)
  {
    std::cout << "It's your turn. Please choose a chess piece." << std::endl;
    Cell selectedCell = askPlayerForACell();
    return selectedCell;
  }*/

  Cell* getCellFromPlayer(char* msg, bool pieceChosen, ChessView* view)
  {
    //printMsg(msg);
    
    return askPlayerForACell(pieceChosen);
  }

  void invalidCell(char* msg, Cell* cell)
  {
    //std::stringstream ss;
    //ss << char((*cell).colum + 65) << (*cell).rowum + 1 << ": " << msg;
   //printErrorMsg(ss.str());
    printf("%c", ((*cell).colum + 65));
    printf("%d", ((*cell).rowum + 1 ));
    printf(": ");
    printf("%s", msg);
    
  }

  void pieceMoved(Player* player, Cell* from, Cell* to)
  {

    printf("%s", getName(player));
    printf(" moved a piece: ");
    printf("%c", ((*from).colum + 65));
    printf("%d", ((*from).rowum + 1));
    printf(" to ");
    printf("%c", ((*to).colum + 65));
    printf("%d", ((*to).rowum + 1));
    printf("\n");
  }

  void printMsg(char* msg)
  {

    printf("%s", msg);
  }

  void printErrorMsg(char* err)
  {
    //std::cout << "\033[31m" << err << "\033[0m" << std::endl; dont bother using stderror, as consoleoutput were not a requirement
  }

  Cell* askPlayerForACell(bool pieceChosen)//Dette er metoden som må endres
  {
    //using std::cout;
    //using std::endl;
    //using std::cin;
        char *s=(char*) malloc(sizeof(char)*100);

    //std::string squareInput;
    int col, row;
    while (true) {
      //cout << "Enter square number (e.g. A7, G4 etc."
           //<< (pieceChosen ? " Leave prompt empty to abort." : "")  << "): ";
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

 const char* pieceToString(pieceType type, colorType color)
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

