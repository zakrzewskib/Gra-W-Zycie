#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// making directory
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "ArrayFunctions.h"
#include "GameFunctions.h"
#include "MainFunctions.h"
#include "PNGFunctions.h"

#define OUT_FILE_LENGTH 12 // = strlen("/genXYZ.txt") + 1 , where genXYZ example gen100
#define MAX_NUM_GEN 100    // max number of generation
int main(int argc, char **argv)
{
    int inputFlagUsed = 1;
    int outputFlagUsed = 1;
    int outgenFlagUsed = 1;

    int r, c, genI;
    int *makeGen = NULL;
    int gen = 0;
    FILE *in = NULL;
    FILE *out = NULL;
    char *outputDir = NULL;
    char *outGenFile = NULL;

    if (argc == 1)
    {
        //printf("No call arguments!\n");
        help();
        return 1;
    }

    for (int i = 1; i < argc; i++)
    {
        if ((strcmp(argv[i], "-input") == 0) && inputFlagUsed)
        {
            if (++i >= argc)
            {
                //printf("No input file!\n");
                return 2;
            }

            if (nextArgumentIsNotFlag(argv[i]))
            {
                if ((in = fopen(argv[i], "r")) == NULL)
                {
                    //printf("File %s doesn't exist!\n", argv[i]);
                    return 3;
                }
                //printf("Opened file: %s \n", argv[i]);
            }
            else
            {
                //printf("No name of input file! \n");
                return 2;
            }
            inputFlagUsed--;
        }

        else if ((strcmp(argv[i], "-output") == 0) && outputFlagUsed)
        {

            if (++i >= argc)
            {
                //printf("No output directory!\n");
                return 2;
            }

            if (nextArgumentIsNotFlag(argv[i]))
            {
                //printf("Creating directory: %s \n", argv[i]);
                outputDir = argv[i];
            }
            else
            {
                //printf("No name of output directory!\n");
                return 2;
            }
            outputFlagUsed--;
        }

        else if ((strcmp(argv[i], "-h") == 0))
        {
            help();
            return 1;
        }

        else if ((strcmp(argv[i], "-outgen") == 0) && outgenFlagUsed)
        {
            if (++i >= argc)
            {
                //printf("No outgen! \n");
                return 2;
            }
            if (nextArgumentIsNotFlag(argv[i]) && (strcmp(argv[i], "-SBS") != 0))
            {
                if (isInterger(argv[i]) && ((gen = atoi(argv[i])) <= MAX_NUM_GEN))
                {
                    //printf("Number of generations is %s \n", argv[i]);

                    if ((makeGen = malloc(gen * sizeof(*makeGen))) == NULL)
                    {
                        return 9;
                    }

                    memset(makeGen, 0, sizeof(*makeGen) * gen);
                    i++;
                }
                else
                {
                    //printf("invalid generation number! \n");
                    return 5;
                }
            }
            else
            {
                //printf("No generation number! \n");
                return 2;
            }

            if (i < argc && (strcmp(argv[i], "-SBS") == 0))
            {
                //printf("STEB BY STEP option\n");
                for (int z = 0; z < gen; z++)
                {
                    makeGen[z] = 1;
                }
            }

            else if (i < argc && isInterger(argv[i]))
            {
                makeGen[atoi(argv[i]) - 1] = 1;
                i++;
                while (i < argc)
                {
                    if (!isInterger(argv[i]))
                    {
                        i--;
                        break;
                    }
                    if (gen < atoi(argv[i]))
                    {
                        //printf("Too large number: %s < gen \n", argv[i]);
                        return 7;
                    }
                    makeGen[atoi(argv[i]) - 1] = 1;
                    i++;
                }
            }
            else
            {
                //printf("No SBS option and no X Y Z option, only last generation will be saved\n");
                makeGen[gen - 1] = 1;
                i--;
            }
            outgenFlagUsed--;
        }
        else
        {
            //printf("Invalid argument: %s!\n", argv[i]);
            return 2;
        }
    }

    if (noRequiredArguments(outgenFlagUsed, inputFlagUsed))
    {
        return 6;
    }

    int **arr = NULL;
    if ((arr = download2DArrayFromFile(in, &genI, &r, &c)) == NULL)
    {
        //printf("Wrong data format!\n");
        return 4;
    }
    if (genI >= gen)
    {
        //printf("Generation in file is bigger that  entered generation \n");
        return 10;
    }
    int **newArr = allocate2DArray(r, c);
    copyArrayToNewArray(r, c, arr, newArr);

    if (!outputFlagUsed)
    {
        if ((outGenFile = malloc(strlen(outputDir) * sizeof(*outGenFile) + OUT_FILE_LENGTH)) == NULL)
        {
            return 9;
        }
        strcpy(outGenFile, outputDir);
        struct stat st = {0};
        if (stat(outGenFile, &st) == -1)
        {
            mkdir(outGenFile, 0700);
        }
        strncat(outGenFile, "/gen", 4);
    }
    else
    {
        if ((outGenFile = malloc(sizeof(*outGenFile) * OUT_FILE_LENGTH)) == NULL)
        {
            return 9;
        }
        strcpy(outGenFile, "gen");
    }

    int length = strlen(outGenFile);

    while (genI < gen)
    {
        if (genI % 2 == 0)
        {
            if (makeNewGeneration(arr, newArr, r, c, genI, outGenFile, length, out, makeGen) == -8)
            {
                return 8;
            }
        }
        else
        {
            if (makeNewGeneration(newArr, arr, r, c, genI, outGenFile, length, out, makeGen) == -8)
            {
                return 8;
            }
        }

        genI++;
    }

    freeAll(arr, newArr, r, c, makeGen, outGenFile);
    return 0;
}
