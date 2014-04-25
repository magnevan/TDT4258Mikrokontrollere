#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <signal.h>

#define FILEPATH "/dev/fb0"
#define GAMEPAD "/dev/gamepad"

#define FILESIZE (320*240)
struct fb_copyarea rect;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;

FILE* gamepad;

void init_gamepad();

/* la oss lage et 8x8 rutenett som dekker hele skjermen. Vi bruker to forskjellige farger. Hver brikketype har en enkel form (en tilfeldig sammensetning av piksler som representerer hver brikke). Hver brikke er angitt med en "offset" adresse relativt til en blokk ( relativ addresse angitt innenfor en range av høyde/8, bredde/8). Offset adressen blir da konstant, og den totale adressen vil da bare være en utskrift av 8x8 matrisen.*/
int main(int argc, char *argv[])
{
    rect.dx=0;
    rect.dy=0;
    rect.width=64;
    rect.height=32;

    printf("Hello World, I'm game!!!! 1\n");
    int  fd = open(FILEPATH, O_RDWR);
    if (fd == -1) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    short*  map = mmap(0, FILESIZE, PROT_WRITE, MAP_SHARED, fd, 0);

    /* screenclear(map,fd); */
    drawboard(map, fd);

    munmap(map,FILESIZE);

    init_gamepad();
    while(1) pause();

    exit(EXIT_SUCCESS);
}

void button_handler(int signo)
{
    int raw_input = fgetc(gamepad);
    int button = 1;

    while (raw_input > 1) {
        raw_input >>= 1;
        button++;
    }

    printf("button %d\n", button);
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
            *(map+i*320+j)=0xF;
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
