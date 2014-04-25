
#include <sys/stat.h>

#include <sys/ioctl.h>
#include <signal.h>
#include "screen.h"

//#define FILEPATH "/dev/fb0"
#define GAMEPAD "/dev/gamepad"

#define LIGHT_BLUE 0x7dcf
#define DARK_BLUE  0x0f77

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
            color = (r%2) == (c%2) ? LIGHT_BLUE : DARK_BLUE;
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
    boardcolor = (row%2) == (col%2) ? DARK_BLUE : LIGHT_BLUE;
    for(; i<320*30*(7-row+1); i+=320)
    {
        for(j=30*col; j<30*(col+1); j++) {
            *(map+i+j) = boardcolor;
        }
    }

    rect.dx = col * 30;
    rect.dy = (7-row) * 30;
    rect.width = 30;
    rect.height = 30;
    ioctl(fd, 0x4680, &rect);
}

int* getPictureForType(pieceType type)
{
    int* pic = malloc(sizeof(int) * 30);
    int i;
    for (i = 0; i < 30; i++)
        pic[i] = 0;

    switch (type) {
        case BISHOP:
            pic[0] = 0;
            pic[1] = 0;
            pic[2] = 0;
            pic[3] = 0;
            pic[4] = 49152;
            pic[5] = 122880;
            pic[6] = 49152;
            pic[7] = 49152;
            pic[8] = 258048;
            pic[9] = 522240;
            pic[10] = 1047552;
            pic[11] = 2047488;
            pic[12] = 1973760;
            pic[13] = 2047488;
            pic[14] = 4144896;
            pic[15] = 2096640;
            pic[16] = 2096640;
            pic[17] = 789504;
            pic[18] = 522240;
            pic[19] = 264192;
            pic[20] = 1047552;
            pic[21] = 258048;
            pic[22] = 16777152;
            pic[23] = 33505248;
            pic[24] = 33431520;
            pic[25] = 0;
            pic[26] = 0;
            pic[27] = 0;
            pic[28] = 0;
            pic[29] = 0;
            break;
        case ROOK:
            pic[0] = 0;
            pic[1] = 0;
            pic[2] = 0;
            pic[3] = 0;
            pic[4] = 0;
            pic[5] = 0;
            pic[6] = 2671872;
            pic[7] = 3794688;
            pic[8] = 4194048;
            pic[9] = 4194048;
            pic[10] = 4194048;
            pic[11] = 2096640;
            pic[12] = 525312;
            pic[13] = 1047552;
            pic[14] = 1047552;
            pic[15] = 1047552;
            pic[16] = 1047552;
            pic[17] = 2096640;
            pic[18] = 2096640;
            pic[19] = 2096640;
            pic[20] = 1049088;
            pic[21] = 4194048;
            pic[22] = 8388480;
            pic[23] = 8388480;
            pic[24] = 8388480;
            pic[25] = 0;
            pic[26] = 0;
            pic[27] = 0;
            pic[28] = 0;
            pic[29] = 0;
            break;
        case KING:
            pic[0] = 0;
            pic[1] = 0;
            pic[2] = 0;
            pic[3] = 0;
            pic[4] = 0;
            pic[5] = 49152;
            pic[6] = 122880;
            pic[7] = 49152;
            pic[8] = 49152;
            pic[9] = 7915392;
            pic[10] = 13056192;
            pic[11] = 20108064;
            pic[12] = 58271648;
            pic[13] = 41758608;
            pic[14] = 41869200;
            pic[15] = 58646448;
            pic[16] = 25042848;
            pic[17] = 29310816;
            pic[18] = 14556864;
            pic[19] = 6291840;
            pic[20] = 4194048;
            pic[21] = 4144896;
            pic[22] = 3144960;
            pic[23] = 2146560;
            pic[24] = 4194048;
            pic[25] = 0;
            pic[26] = 0;
            pic[27] = 0;
            pic[28] = 0;
            pic[29] = 0;
            break;
        case QUEEN:
            pic[0] = 0;
            pic[1] = 0;
            pic[2] = 0;
            pic[3] = 0;
            pic[4] = 0;
            pic[5] = 0;
            pic[6] = 924672;
            pic[7] = 924672;
            pic[8] = 924672;
            pic[9] = 399360;
            pic[10] = 924672;
            pic[11] = 59718768;
            pic[12] = 59718768;
            pic[13] = 26213472;
            pic[14] = 16777152;
            pic[15] = 8388480;
            pic[16] = 8388480;
            pic[17] = 4194048;
            pic[18] = 4194048;
            pic[19] = 3146496;
            pic[20] = 3668736;
            pic[21] = 2047488;
            pic[22] = 3619584;
            pic[23] = 3146496;
            pic[24] = 4194048;
            pic[25] = 0;
            pic[26] = 0;
            pic[27] = 0;
            pic[28] = 0;
            pic[29] = 0;
            break;
        case KNIGHT:
            pic[0] = 0;
            pic[1] = 0;
            pic[2] = 0;
            pic[3] = 0;
            pic[4] = 0;
            pic[5] = 8192;
            pic[6] = 28672;
            pic[7] = 129024;
            pic[8] = 261120;
            pic[9] = 491008;
            pic[10] = 1998080;
            pic[11] = 4193920;
            pic[12] = 16776832;
            pic[13] = 14677696;
            pic[14] = 16772672;
            pic[15] = 16772672;
            pic[16] = 3939904;
            pic[17] = 7405120;
            pic[18] = 261824;
            pic[19] = 523968;
            pic[20] = 1048256;
            pic[21] = 2096832;
            pic[22] = 2097088;
            pic[23] = 2097088;
            pic[24] = 2097088;
            pic[25] = 0;
            pic[26] = 0;
            pic[27] = 0;
            pic[28] = 0;
            pic[29] = 0;
            break;
        case PAWN:
            pic[0] = 0;
            pic[1] = 0;
            pic[2] = 0;
            pic[3] = 0;
            pic[4] = 0;
            pic[5] = 0;
            pic[6] = 0;
            pic[7] = 122880;
            pic[8] = 258048;
            pic[9] = 258048;
            pic[10] = 258048;
            pic[11] = 258048;
            pic[12] = 122880;
            pic[13] = 522240;
            pic[14] = 1047552;
            pic[15] = 122880;
            pic[16] = 122880;
            pic[17] = 258048;
            pic[18] = 258048;
            pic[19] = 522240;
            pic[20] = 522240;
            pic[21] = 1047552;
            pic[22] = 4194048;
            pic[23] = 4194048;
            pic[24] = 4194048;
            pic[25] = 0;
            pic[26] = 0;
            pic[27] = 0;
            pic[28] = 0;
            pic[29] = 0;
            break;
    }

    return pic;
}

void printpiece(short* map, int fd, pieceType type, colorType color, int col, int row)
{
    short piececolor;
    short clearcolor;
    int x,y;
    int* picture = getPictureForType(type);
    piececolor = (color == BLACK) ? 0xFFFF : 0x0000;//change color
    clearcolor = (row%2) == (col%2) ? DARK_BLUE : LIGHT_BLUE;
    for (y = 0; y < 30; y++)
    {
        for (x = 0; x < 30; x++)
        {
           *(map + 30*320*(7-row) + 320*y + 30*col+x) 
               = ((picture[y] & (1 << x)) > 0) ? piececolor : clearcolor;  
        }
    }

    free(picture);
    printf("printpiece %d %d\n", type, color);

    
    rect.dx = col * 30;
    rect.dy = (7-row) * 30;
    rect.width = 30;
    rect.height = 30;
    ioctl(fd, 0x4680, &rect);
}

void printmarker(short* map, int fd, int on, int col, int row)
{
    short markcolor = 
        on ? 0x7fc0 : 
        (row%2) == (col%2) ? DARK_BLUE : 
                             LIGHT_BLUE;

    int x,y;

    y = 0;
    for (x = 0; x < 30; x++)
       *(map + 30*320*(7-row) + 320*y + 30*col+x) = markcolor;

    y = 28;
    for (x = 0; x < 30; x++)
       *(map + 30*320*(7-row) + 320*y + 30*col+x) = markcolor;

    x = 0;
    for (y = 0; y < 29; y++)
       *(map + 30*320*(7-row) + 320*y + 30*col+x) = markcolor;

    x = 29;
    for (y = 0; y < 29; y++)
       *(map + 30*320*(7-row) + 320*y + 30*col+x) = markcolor;

    rect.dx = col * 30;
    rect.dy = (7-row) * 30;
    rect.width = 30;
    rect.height = 30;
    ioctl(fd, 0x4680, &rect);
}
