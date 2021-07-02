#include <stdio.h>
#ifndef ARRAYFUNCTIONS_H
#define ARRAYFUNCTIONS_H
int **allocate2DArray(int r, int c);
void print2DArrayToFile(int **arr, int r, int c, int gen, FILE *out);
int **download2DArrayFromFile(FILE *in, int *gen, int *r, int *c);
void free2DArray(int **arr, int r, int c);
#endif
