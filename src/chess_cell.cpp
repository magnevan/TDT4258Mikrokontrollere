#include "chess_cell.h"

Cell* Cellinit(int c, int r) {
Cell* cell=(Cell *) malloc(sizeof(Cell));
(*cell).colum=c;
(*cell).rowum=r;
};//may have to move this
    bool cellequals(Cell cell1, Cell cell2)//operator==(const Cell & c)
    {
     if(cell1.colum == cell2.colum && cell1.rowum == cell2.rowum)
     return true;
     
      return false;
    }

    bool nequals(Cell cell1, Cell cell2)//bool operator!=(const Cell & c)
    {
    if(cellequals(cell1,cell2))
    return false;
    else
    return true;
      //return !(operator==(c));
    }