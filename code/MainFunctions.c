#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "GameFunctions.h"
#include "ArrayFunctions.h"
#include "PNGFunctions.h"

char *writeOutFile(char *outGenFile, int length, int genI)
{
    sprintf(outGenFile + length, "%d.txt", genI);
    outGenFile - length;
    return outGenFile;
}
char *writeOutFilePNG(char *outGenFile, int length, int genI)
{
    sprintf(outGenFile + length, "%d.png", genI);
    outGenFile - length;
    return outGenFile;
}

void help()
{
    printf("Required arguments are: \n-input <name of input file> and -outgen <number of generations> \n");
    printf("Additional argument: \n-output <name of directory with PNG and TXT files> \n");
    printf("Additional options for -outgen argument: \n-outgen <n> -SBS or -outgen <n> <x> <y> <z> \n");
    printf("-SBS will save all generations to n. generation \n<x> <y> <z> will save generation number x, y and z\n");
}

int isInterger(char *string)
{
    int num1;
    double tmp1;
    if (sscanf(string, "%lf", &tmp1) == 1)
    {
        num1 = tmp1;
        if (num1 < tmp1 || num1 < 1)
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
    return 1;
}
int nextArgumentIsNotFlag(char *arg)
{
    if ((strcmp(arg, "-input") == 0) || (strcmp(arg, "-output") == 0) || (strcmp(arg, "-h") == 0) || ((strcmp(arg, "-outgen") == 0)))
    {
        return 0;
    }
    return 1;
}
int noRequiredArguments(int outgenFlagUsed, int inputFlagUsed)
{
    if (outgenFlagUsed)
    {
        printf("No required argument -outgen!\n");
        help();
        return 1;
    }
    else if (inputFlagUsed)
    {
        printf("No required argument -input!\n");
        help();
        return 1;
    }
    return 0;
}

int makeNewGeneration(int **arr, int **newArr, int r, int c, int genI, char *outGenFile, int length, FILE *out, int *makeGen)
{
    makeNextGeneration2DArray(arr, newArr, r, c);
    if (makeGen[genI])
    {
        if ((out = fopen(writeOutFile(outGenFile, length, genI + 1), "w")) == NULL)
        {
            return -8;
        }
        print2DArrayToFile(newArr, r, c, genI + 1, out);
        fclose(out);
        if ((out = fopen(writeOutFile(outGenFile, length, genI + 1), "r")) == NULL)
        {
            return -8;
        }
        makePNGFile(writeOutFilePNG(outGenFile, length, genI + 1), out);
        fclose(out);
    }
    return 0;
}

void freeAll(int **arr, int **newArr, int r, int c, int *makeGen, char *outGenFile)
{
    free2DArray(arr, r, c);
    free2DArray(newArr, r, c);
    free(makeGen);
    free(outGenFile);
}

void copyArrayToNewArray(int r, int c, int **arr, int **newArr)
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            newArr[i][j] = arr[i][j];
        }
    }
}
