// Kontrollert av Eirik FLogard



#include "chess_player.h"
#include <stdlib.h>


Player* Player0() {
    Player* player=(Player *) malloc(sizeof(Player));
    return player;
}
Player* Player1(char* pname, playerType ptype, colorType pcolor) {
    Player* player=(Player *) malloc(sizeof(Player));
    (*player).name=pname;
    (*player).type=ptype;
    (*player).color=pcolor;
    return player;

}
char* getName(Player* player) { return (*player).name; }
playerType getPlayerType(Player* player) { return (*player).type; }
colorType getPlayerColor(Player* player) { return (*player).color; }
