
#include <sys/stat.h>

#include <sys/ioctl.h>
#include <signal.h>
#include "screen.h"

//#define FILEPATH "/dev/fb0"
#define GAMEPAD "/dev/gamepad"


struct fb_copyarea rect;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;

int lastButtonPressed = -1;

FILE* gamepad;

void init_gamepad();

/* la oss lage et 8x8 rutenett som dekker hele skjermen. Vi bruker to forskjellige farger. Hver brikketype har en enkel form (en tilfeldig sammensetning av piksler som representerer hver brikke). Hver brikke er angitt med en "offset" adresse relativt til en blokk ( relativ addresse angitt innenfor en range av høyde/8, bredde/8). Offset adressen blir da konstant, og den totale adressen vil da bare være en utskrift av 8x8 matrisen.*/
/*int main(int argc, char *argv[])
  {
  int fd = open(FILEPATH, O_RDWR);
  if (fd == -1) {
  perror("Error opening file for reading");
  exit(EXIT_FAILURE);
  }

  short* map = mmap(0, FILESIZE, PROT_WRITE, MAP_SHARED, fd, 0);

  screenclear(map,fd); 
  drawboard(map, fd);

  munmap(map,FILESIZE);

  init_gamepad();
  while(1) pause();

  exit(EXIT_SUCCESS);
  }*/
//insert a dynamic allocated array right here to writeback the vlaue from the button 
void button_handler(int signo)
{
    int raw_input = fgetc(gamepad);
    int button = 1;

    while (raw_input > 1) {
        raw_input >>= 1;
        button++;
    }

    lastButtonPressed = button;

    printf("button %d\n", button);

}

int getLastButtonPressed() {
    int toReturn = lastButtonPressed;
    lastButtonPressed = -1;
    return toReturn;
}

void init_gamepad()
{
    gamepad = fopen(GAMEPAD, "rb");
    signal(SIGIO, &button_handler);
    fcntl(fileno(gamepad), F_SETOWN, getpid());
    long oflags = fcntl(fileno(gamepad), F_GETFL);
    fcntl(fileno(gamepad), F_SETFL, oflags | FASYNC);
    printf("gamepad initialized\n");
}

int screenclear(short* map, int fd)
{
    //legg til try/catch eller noe
    rect.dx=0;
    rect.dy=0;
    rect.width=319;
    rect.height=239;
    long i=1;
    long j=1;
    while(i<=239) {
        j=1;
        while(j<=319) {
            *(map+i*320+j)=0x0000;
            j++;
        }

        i++;
    }
    ioctl(fd, 0x4680, &rect);
    return 0;
}

int drawboard(short* map, int fd)
{
    rect.dx = 0;
    rect.dy = 0;
    rect.width = 240;
    rect.height = 240;
    int i, j, r, c;
    short color;
    for (i = 0; i < 240; i++) {
        for (j = 0; j < 240; j++) {
            r = i / 30;
            c = j / 30;
            color = (r%2) == (c%2) ? 0x000F : 0x0006;
            *(map+i*320+j) = color;
        }
    }
    ioctl(fd, 0x4680, &rect);
    return 0;
}

void squareclear(short* map, int fd, int col, int row)
{
    //rect.dx = 0;
    // rect.dy = 0;
    // rect.width = 240;
    //rect.height = 240;
    //optimization vs robustness: we can specify the exact square where we need to update using the variables above. However this may decrease robustness by introdusing artifacts on screen
    int  r, c;
    long i=320*30*(7-row);
    long j=30*(col);
    short boardcolor;
    r = i / 30;
    c = j / 30;
    boardcolor = (row%2) == (col%2) ? 0x0006 : 0x000f;
    for(; i<320*30*(7-row+1); i+=320)
    {
        for(j=30*col; j<30*(col+1); j++) {
            *(map+i+j) = boardcolor;
        }
    }
    ioctl(fd, 0x4680, &rect);



}

void printpieceKing(short* map, int fd, colorType color, int col, int row)
{
    //rect.dx = 0;
    // rect.dy = 0;
    // rect.width = 240;
    //rect.height = 240;
    //need to take 7-row for each piece else the output on the screen get upside down
    long i=320*30*(7-row);
    long j=30*(col);
    short boardcolor;
    boardcolor = (color == BLACK) ? 0xabcd : 0xa215;//change color
    for(; i<320*30*(7-row+1); i+=320)
    {
        for(j=30*col; j<30*(col+1); j++)//insert kewl patterns with i and j to create figures
        {

            *(map+i+j) = boardcolor;
        }
    }
    ioctl(fd, 0x4680, &rect);
}
void printpieceQueen(short* map, int fd, colorType color, int col, int row)
{
    //rect.dx = 0;
    // rect.dy = 0;
    // rect.width = 240;
    //rect.height = 240;
    long i=320*30*(7-row);
    long j=30*col;
    short boardcolor;
    boardcolor = (color == BLACK) ? 0xdefa : 0x5432;//change color
    for(; i<320*30*(7-row+1); i+=320)
    {
        for(j=30*col; j<30*(col+1); j++)//insert kewl patterns with i and j to create figures
        {

            *(map+i+j) = boardcolor;
        }
    }
    ioctl(fd, 0x4680, &rect);

}
void printpieceKnight(short* map, int fd, colorType color, int col, int row)
{
    //rect.dx = 0;
    // rect.dy = 0;
    // rect.width = 240;
    //rect.height = 240;
    long i=320*30*(7-row);
    long j=30*col;
    short boardcolor;
    boardcolor = (color == BLACK) ? 0xbaad : 0x0246;//change color
    for(; i<320*30*(7-row+1); i+=320)
    {
        for(j=30*col; j<30*(col+1); j++)//insert kewl patterns with i and j to create figures
        {

            *(map+i+j) = boardcolor;
        }
    }
    ioctl(fd, 0x4680, &rect);

}
void printpieceBishop(short* map, int fd, colorType color, int col, int row)
{
    //rect.dx = 0;
    // rect.dy = 0;
    // rect.width = 240;
    //rect.height = 240;
    long i=320*30*(7-row);
    long j=30*col;
    short boardcolor;
    boardcolor = (color == BLACK) ? 0x9afd : 0x6420;//change color
    for(; i<320*30*(7-row+1); i+=320)
    {
        for(j=30*col; j<30*(col+1); j++)//insert kewl patterns with i and j to create figures
        {

            *(map+i+j) = boardcolor;
        }
    }
    ioctl(fd, 0x4680, &rect);

}
void printpieceRook(short* map, int fd, colorType color, int col, int row)
{
    //rect.dx = 0;
    // rect.dy = 0;
    // rect.width = 240;
    //rect.height = 240;
    long i=320*30*(7-row);
    long j=30*col;
    short boardcolor;
    boardcolor = (color == BLACK) ? 0xfade : 0x4246;//change color
    for(; i<320*30*(7-row+1); i+=320)
    {
        for(j=30*col; j<30*(col+1); j++)//insert kewl patterns with i and j to create figures
        {

            *(map+i+j) = boardcolor;
        }
    }
    ioctl(fd, 0x4680, &rect);

}
void printpiecePawn(short* map, int fd, colorType color, int col, int row)
{
    //rect.dx = 0;
    // rect.dy = 0;
    // rect.width = 240;
    //rect.height = 240;
    long i=320*30*(7-row);
    long j=30*col;
    short boardcolor;
    boardcolor = (color == BLACK) ? 0xdaea : 0x1427;//change color
    for(; i<320*30*(7-row+1); i+=320)
    {
        for(j=30*col; j<30*(col+1); j++)//insert kewl patterns with i and j to create figures
        {

            *(map+i+j) = boardcolor;
        }
    }
    ioctl(fd, 0x4680, &rect);

}


