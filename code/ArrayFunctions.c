#include "ArrayFunctions.h"
#include <stdlib.h>

int **allocate2DArray(int r, int c)
{
	int **arr = malloc(r * sizeof(int *));
	for (int i = 0; i < c; i++)
		arr[i] = malloc(c * sizeof(int));
	return arr;
}

void free2DArray(int **arr, int r, int c)
{
	for (int i = 0; i < c; i++)
	{
		free(arr[i]);
	}
	free(arr);
}
void print2DArrayToFile(int **arr, int r, int c, int gen, FILE *out)
{
	fprintf(out, "%d %d\n", r, c);
	fprintf(out, "%d\n", gen);

	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			fprintf(out, "%d ", arr[i][j]);
		}
		fprintf(out, "\n");
	}
}

int **download2DArrayFromFile(FILE *in, int *gen, int *r, int *c)
{
	int r1, c1, gen1;

	if (fscanf(in, "%d", &r1) == EOF || r1 < 3 || r1 > 100)
	{
		return NULL;
	}

	if (fscanf(in, "%d", &c1) == EOF || c1 < 3 || c1 > 100)
	{
		return NULL;
	}

	if (fscanf(in, "%d", &gen1) == EOF || gen1 < 0 || gen1 > 100)
	{
		return NULL;
	}

	*r = r1;
	*c = c1;
	*gen = gen1;

	int **arr = allocate2DArray(r1, c1);

	for (int i = 0; i < r1; i++)
	{
		for (int j = 0; j < c1; j++)
		{
			if (fscanf(in, "%d", &arr[i][j]) == EOF)
			{
				return NULL;
			}
		}
	}
	int tmp;
	if (fscanf(in, "%d", &tmp) != EOF)
	{
		return NULL;
	}
	return arr;
}
