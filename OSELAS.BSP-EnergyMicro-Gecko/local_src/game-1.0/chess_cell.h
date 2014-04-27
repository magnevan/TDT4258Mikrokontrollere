//kontrollert av eirik
#include <stdio.h>
#include <stdlib.h>
#ifndef CHESS_CELL_H_
#define CHESS_CELL_H_
typedef enum { false, true } bool;

typedef struct Cell Cell;//we want a Cell-datatype
struct Cell
{
    int colum;
    int rowum;


};

Cell* Cellinit(int c, int r);
bool cellequals(Cell cell1, Cell cell2);

bool nequals(Cell cell1, Cell cell2);




#endif
