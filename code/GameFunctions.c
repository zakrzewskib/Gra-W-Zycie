#include "GameFunctions.h"
#include "ArrayFunctions.h"

int countAliveNeighbours(int **arr, int r, int c, int i, int j)
{
    int neighbours = 0;
    int yPosition = i - 1;
    int xPosition;

    for (int w = 0; w < 3; w++)
    {
        if (yPosition >= 0 && yPosition < r)
        {
            xPosition = j - 1;
            for (int z = 0; z < 3; z++)
            {
                if (xPosition >= 0 && xPosition < c)
                {
                    if (yPosition == i && xPosition == j)
                    {
                    }
                    else if (arr[yPosition][xPosition] == 1)
                    {
                        neighbours++;
                    }
                }
                xPosition++;
            }
        }
        yPosition++;
    }
    return neighbours;
}

void **makeNextGeneration2DArray(int **arr, int **newArr, int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {

            if (arr[i][j] == 1)
            {
                if (countAliveNeighbours(arr, r, c, i, j) == 2)
                {
                    newArr[i][j] = arr[i][j];
                }
                else if (countAliveNeighbours(arr, r, c, i, j) == 3)
                {
                    newArr[i][j] = arr[i][j];
                }
                else
                {
                    newArr[i][j] = 0;
                }
            }
            else if (arr[i][j] == 0)
            {

                if (countAliveNeighbours(arr, r, c, i, j) == 3)
                {
                    newArr[i][j] = 1;
                }
                else
                {
                    newArr[i][j] = arr[i][j];
                }
            }
        }
    }
}
