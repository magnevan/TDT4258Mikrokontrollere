// Kontrollert av eirik flogard

#include "chess_game.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
  bool termPlayer1 = true;
  bool termView = true;

  std::string arg;

  for (int i = 1; i < argc; i++) {
    arg = argv[i];
    if (arg == "-t" || arg == "--terminalplayers")
      termPlayer1 = true;
  }

  ChessGame* chessgame=chessgame1((termView ? TERM : GUI),
                        (termPlayer1 ? TERMINAL : BOT),
                        TERMINAL);
  try {
    startGame(chessgame);
    free((*chessgame).players[0]);
    free((*chessgame).players[1]);
    free((*chessgame).view);
    free(chessgame);
  } catch (std::string err) {
    std::cout << err << std::endl;
        free((*chessgame).players[0]);
    free((*chessgame).players[1]);
    free((*chessgame).view);
    free(chessgame);
    return 1;
  }
}
