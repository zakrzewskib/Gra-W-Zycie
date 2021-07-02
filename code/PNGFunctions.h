#ifndef PNGFUNCTIONS_H
#define PNGFUNCTIONS_H
#include <stdio.h>
void write_png_file(char *file_name);
void process_file(FILE *in);
void makePNGFile(char *name, FILE *in);
#endif