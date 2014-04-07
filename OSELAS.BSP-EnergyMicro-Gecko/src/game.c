#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#define FILEPATH "/dev/fb0"

#define FILESIZE (320*240)
struct fb_copyarea rect;
     struct fb_var_screeninfo vinfo;
     struct fb_fix_screeninfo finfo;

/* la oss lage et 8x8 rutenett som dekker hele skjermen. Vi bruker to forskjellige farger. Hver brikketype har en enkel form (en tilfeldig sammensetning av piksler som representerer hver brikke). Hver brikke er angitt med en "offset" adresse relativt til en blokk ( relativ addresse angitt innenfor en range av høyde/8, bredde/8). Offset adressen blir da konstant, og den totale adressen vil da bare være en utskrift av 8x8 matrisen.*/
int main(int argc, char *argv[])
{


rect.dx=0;
rect.dy=0;
rect.width=64;
rect.height=32;


printf("Hello World, I'm game!!!!\n");
  int  fd = open(FILEPATH, O_RDWR);
    if (fd == -1) {
	perror("Error opening file for reading");
	exit(EXIT_FAILURE);
    }

short*  map = mmap(0, FILESIZE, PROT_WRITE, MAP_SHARED, fd, 0);

screenclear(map,fd);

munmap(map,FILESIZE);
	exit(EXIT_SUCCESS);
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
while(i<=239)
{
j=1;
while(j<=319)
{
*(map+i*320+j)=0x0;
j++;
}

i++;
}
ioctl(fd, 0x4680, &rect);
return 0;
}
