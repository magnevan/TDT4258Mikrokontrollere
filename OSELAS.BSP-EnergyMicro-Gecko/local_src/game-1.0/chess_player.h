// Kontrollert av Eirik Flogard

#ifndef PLAYER_H_
#define PLAYER_H_


#include "player_types.h"
#include "color_types.h"


typedef struct Player
{
    playerType type;
    char* name;
    colorType color;
} Player;

Player* Player0();
Player* Player1(char* name, playerType type, colorType color);
playerType getPlayerType(Player* player);
char* getName(Player* player);
colorType getPlayerColor(Player* player);



#endif
