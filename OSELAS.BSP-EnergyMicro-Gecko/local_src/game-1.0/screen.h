#ifndef SCREEN_H_
#define SCREEN_H_
/*this class is responsible for displaying things on the screen of the devboard*/
#include "piece_types.h"
#include "color_types.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/fb.h>
#include <fcntl.h>
#define FILEPATH "/dev/fb0"
#define FILESIZE (320*240)

void button_handler(int signo);
int getLastButtonPressed();
void init_gamepad();
int screenclear(short* map, int fd);
int drawboard(short* map, int fd);
void squareclear(short* map, int fd, int col, int row);
//void printpiece(short* map, int fd,pieceType type, colorType color, int col, int row);
void printpiecePawn(short* map, int fd, colorType color, int col, int row);
void printpieceKing(short* map, int fd, colorType color, int col, int row);
void printpieceQueen(short* map, int fd, colorType color, int col, int row);
void printpieceRook(short* map, int fd, colorType color, int col, int row);
void printpieceBishop(short* map, int fd, colorType color, int col, int row);
void printpieceKnight(short* map, int fd, colorType color, int col, int row);
#endif
