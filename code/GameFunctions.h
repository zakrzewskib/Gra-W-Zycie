#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H
void **makeNextGeneration2DArray(int **arr, int **newArr, int r, int c);
int countAliveNeighbours(int **arr, int r, int c, int i, int j);
#endif
