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

    screenclear(map,fd);

    munmap(map,FILESIZE);

    init_gamepad();
    while(1) pause();

    exit(EXIT_SUCCESS);
}

void button_handler(int signo)
{
    int raw_input = fgetc(gamepad);
    int button = 1;
    int test = raw_input;

    while (raw_input > 1) {
        raw_input >>= 1;
        button++;
    }

    printf("button %d %d\n", button, test);
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
            *(map+i*320+j)=0x0;
            j++;
        }

        i++;
    }
    ioctl(fd, 0x4680, &rect);
    return 0;
}
