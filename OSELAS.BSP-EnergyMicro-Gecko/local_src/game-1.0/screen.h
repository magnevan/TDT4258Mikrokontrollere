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
//buttonhandler
void button_handler(int signo);
int getLastButtonPressed();
void init_gamepad();
//screenclear clears the screen to get that ugly penguin away
int screenclear(short* map, int fd);
//drawboard draws the board
int drawboard(short* map, int fd);
//squareclear removes a piece from a square graphically
void squareclear(short* map, int fd, int col, int row);
int* getPictureForType(pieceType type);
//print piece, prints out a piece
void printpiece(short* map, int fd,pieceType type, colorType color, int col, int row);
//printmarker prints out the yellow marker on the board
void printmarker(short* map, int fd, int on, int col, int row);
#endif
