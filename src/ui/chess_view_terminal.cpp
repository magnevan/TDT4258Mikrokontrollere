// Kontrollert av eirik flogard

#include <string>
#include <iostream>
#include <sstream>
#include <limits>

#include "../chess_player.h"
#include "chess_view_terminal.h"
using namespace std;
ChessView*  ChessViewTerm(ChessGame* gameref)
{
return chessview1(gameref);

}


 /* void ChessViewTerm::printPlayers(Player * players)
  {
    for (int i = 0; i < 2; i++) {
      std::cout << players[i].getName() << " is a "
                << (players[i].getType() == BOT ? "bot" : "terminal player")
                << " and has the color "
                << (players[i].getColor() == BLACK ? "black" : "white") << "."
                << std::endl;
    }
  }*/

  /*std::string ChessViewTerm::getName()
  {
    std::cout << "Please enter the name of the second player. If you press "
              << "ENTER it will be chosen for you (Player 2): ";
    std::string input;
    std::getline(std::cin, input);
    return input;
  }*/

  /*bool ChessViewTerm::getNewRound()
  {
    std::cout << "Do you want to start a new round (yes or no)? ";
    std::string input;
    std::cin >> input;
    while (input != std::string("yes")  && input != std::string("no")) {
      std::cout << "Please enter yes or no: ";
      std::cin >> input;
    }

    return input == std::string("yes");
  }*/

  void initializeRound()
  {
    std::cout << "\033[1mStarting a new game of chess.\033[0m" << std::endl;
  }
/*void ChessViewTerm::printBoard(ChessBoard & board)
  {
    //using std::cout;
    //using std::endl;

    ChessPiece* piece;
    pieceType type;
    colorType color;
    int lightBackground = 1;
    std::string colorcode;
    std::string b_colorcode;
    int i, j, col, row;
    int tableStart = 2; // Starten av brettet

    
    for (i = 0; i <= tableStart; i++)
      cout << "-";
    for (i = 0; i < 8; i++)
      cout << "----";
    cout << endl;

    for (i = 1; i < tableStart; i++)
      cout << " ";
    char letter = 'a';
    for (i = 0; i < 8; i++)
      cout << "   " << letter++;
    cout << endl;

    for (i = 0; i < tableStart; i++)
      cout << " ";
    for (i = 0; i < 8; i++)
      cout << " ---";
    
    // TODO: Øverste rad må begynne fra 8
    for (row = 7; row >= 0; row--) {
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
  void printBoard(ChessBoard* board)
  {
    //using std::cout;
    //using std::endl;

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
   //for (i = 0; i <= tableStart; i++)
      //cout << "-";
      
      i=0;
      while(i<8)
      {
      cout << "----";
      i++;
      }
    //for (i = 0; i < 8; i++)
      //cout << "----";
      printf("\n");
    //cout << endl;

    i=1;
    while(i<tableStart)
    {
    printf(" ");
    i++;
    }
    //for (i = 1; i < tableStart; i++)
      //cout << " ";
    char letter = 'a';
    i=0;
    while(i<8)
    {
    printf("  ");
    printf(&letter);
    letter++;
    i++;
    }
    //for (i = 0; i < 8; i++)
      //cout << "   " << letter++;
      printf("\n");
    //cout << endl;

    i=0;
    while(i<tableStart)
    {
    printf(" ");
    i++;
    }
   //for (i = 0; i < tableStart; i++)
     // cout << " ";
     i=0;
     while(i<8)
     {
     printf(" ---");
     i++;
     }
    //for (i = 0; i < 8; i++)
      //cout << " ---";
    
    // TODO: Øverste rad må begynne fra 8
    row=7;
    while(row>=0)
    {
    lightBackground = (row % 2 != 0);
    printf("\n");
    //printf(row+1);//this wont work prob
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
      printMsg("No moves are possible with that chess piece.");
      return;
    }

    Cell cell;
    //std::vector<Cell>::iterator im;

    std::cout << "Valid moves:";
    int i=0;
    //for (im = moves.begin(); im != moves.end(); im++ ) {
    while(i<size){
      std::cout << " " << char(moves[i].colum + 65) << moves[i].rowum + 1;
      i++;
    }
    std::cout << std::endl;
  }

  /*Cell ChessViewTerm::getCellWithPieceFromPlayer(ChessBoard * board,
    Player * pl)
  {
    std::cout << "It's your turn. Please choose a chess piece." << std::endl;
    Cell selectedCell = askPlayerForACell();
    return selectedCell;
  }*/

  Cell* getCellFromPlayer(std::string msg, bool pieceChosen, ChessView* view)
  {
    printMsg(msg);
    return askPlayerForACell(pieceChosen);
  }

  void invalidCell(std::string msg, Cell* cell)
  {
    std::stringstream ss;
    ss << char((*cell).colum + 65) << (*cell).rowum + 1 << ": " << msg;
    printErrorMsg(ss.str());
  }

  void pieceMoved(Player* player, Cell* from, Cell* to)
  {
    std::stringstream ss;
    ss << getName(player) << " moved a piece: " << char((*from).colum + 65)
       << (*from).rowum + 1 << " to " << char((*to).colum + 65) << (*to).rowum + 1;
    printMsg(ss.str());
  }

  void printMsg(std::string msg)
  {
    std::cout << msg << std::endl;
  }

  void printErrorMsg(std::string err)
  {
    std::cout << "\033[31m" << err << "\033[0m" << std::endl;
  }

  Cell* askPlayerForACell(bool pieceChosen)//we have to change this
  {
    using std::cout;
    using std::endl;
    using std::cin;
    
    std::string squareInput;
    int col, row;
    while (true) {
      cout << "Enter square number (e.g. A7, G4 etc."
           << (pieceChosen ? " Leave prompt empty to abort." : "")  << "): ";

      std::string squareInput;
      bool correct = false;
      while (true) {
        std::getline(cin, squareInput);
        if (squareInput.size() == 2) {
          char colInput = squareInput.at(0);
          char rowInput = squareInput.at(1);
          if (colInput < 'A' || colInput > 'h' ||
              (colInput > 'H' && colInput < 'a')) {
            cout << "Invalid column. Should be a character between a and h.\n";
          } else if (rowInput < 49 || rowInput > 56) {
            cout << "Invalid row. Should be an integer between 1 and 8.\n";
          } else {
            col = colInput - (colInput <= 'H' ? 65 : 97);
            row = rowInput - 49;
            break;
          }
        } else if (pieceChosen && squareInput.empty())
        {
        Cell* cell=(Cell*) malloc(sizeof(Cell));
        (*cell).rowum=-1;
        (*cell).colum=-1;
          return cell; // Ugyldig celle, avslutter valget.
        }
        cout << "Please choose a valid square"
             << (pieceChosen ? " (Leave prompt empty to abort.): " : ": ");      
      }
              Cell* cell2=(Cell*) malloc(sizeof(Cell));
                      (*cell2).rowum=row;
        (*cell2).colum=col;
      return cell2;
    }
  }

  std::string pieceToString(pieceType type, colorType color)
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

