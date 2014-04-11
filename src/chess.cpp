// Kontrollert av eirik flogard

#include "chess_game.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
  bool termPlayer1 = false;
  bool termView = true;

  std::string arg;

  for (int i = 1; i < argc; i++) {
    arg = argv[i];
    if (arg == "-t" || arg == "--terminalplayers")
      termPlayer1 = true;
  }

  ChessGame* chessgame=chessgame1((termView ? chess::TERM : chess::GUI),
                        (termPlayer1 ? chess::TERMINAL : chess::BOT),
                        chess::BOT);
  try {
    startGame(chessgame);
    free(chessgame);
  } catch (std::string err) {
    std::cout << err << std::endl;
    free(chessgame);
    return 1;
  }
}
