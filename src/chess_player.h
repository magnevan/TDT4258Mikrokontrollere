// Kontrollert av Eirik Flogard

#ifndef PLAYER_H_
#define PLAYER_H_

//#include <string>

#include "types/player_types.h"
#include "types/color_types.h"


  struct Player
  {
    playerType type;
    char name[200];
    colorType color;
      };
 // public:
    Player* Player0();
    Player* Player1(char* name, playerType type, colorType color);
    playerType getType(Player* player);
    char* getName(Player* player);
    colorType getColor(Player* player);



#endif
