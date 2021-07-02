#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include <png.h>

#include <stdlib.h>
#include "ArrayFunctions.h"

int x, y;

int width, height;
png_byte color_type;
png_byte bit_depth;

png_structp png_ptr;
png_infop info_ptr;
int number_of_passes;
png_bytep *row_pointers;

void write_png_file(char *file_name)
{
  FILE *fp = fopen(file_name, "wb");
  if (!fp)
    printf("[write_png_file] File %s could not be opened for writing", file_name);

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr)
    printf("[write_png_file] png_create_write_struct failed");

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
    printf("[write_png_file] png_create_info_struct failed");

  if (setjmp(png_jmpbuf(png_ptr)))
    printf("[write_png_file] Error during init_io");

  png_init_io(png_ptr, fp);

  if (setjmp(png_jmpbuf(png_ptr)))
    printf("[write_png_file] Error during writing header");

  png_set_IHDR(png_ptr, info_ptr, width, height,
               bit_depth, color_type, PNG_INTERLACE_NONE,
               PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

  png_write_info(png_ptr, info_ptr);

  if (setjmp(png_jmpbuf(png_ptr)))
    printf("[write_png_file] Error during writing bytes");

  png_write_image(png_ptr, row_pointers);

  if (setjmp(png_jmpbuf(png_ptr)))
    printf("[write_png_file] Error during end of write");

  png_write_end(png_ptr, NULL);

  for (y = 0; y < height; y++)
    free(row_pointers[y]);
  free(row_pointers);

  fclose(fp);
}

void process_file(FILE *in)
{
  int gen;
  int **arr = download2DArrayFromFile(in, &gen, &width, &height);

  // Making PNG file bigger
  int scale = 50; // No adjustment to the table size
  int widthBefore = width;
  int heightBefore = height;

  width *= scale;
  height *= scale;

  int **newArr = allocate2DArray(width, height);

    int r = -1;
  int c = -1;
  for (int i = 0; i < width; i++)
  {
    if (i % scale == 0)
    {
      r++;
      if (r >= widthBefore)
        r = 0;
    }

    for (int j = 0; j < height; j++)
    {
      if (j % scale == 0)
      {
        c++;
        if (c >= widthBefore)
          c = 0;
      }
      newArr[i][j] = arr[r][c];
    }
  }

  bit_depth = 8;
  color_type = PNG_COLOR_TYPE_GRAY;

  number_of_passes = 7;
  row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);
  for (y = 0; y < height; y++)
    row_pointers[y] = (png_byte *)malloc(sizeof(png_byte) * width);

  for (y = 0; y < height; y++)
  {
    png_byte *row = row_pointers[y];
    for (x = 0; x < width; x++)
    {
      if (newArr[y][x] == 0)
        row[x] = 255;
      else
        row[x] = 0;
    }
  }
}

void makePNGFile(char *name, FILE *in)
{
  process_file(in);
  write_png_file(name);
}
