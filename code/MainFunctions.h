#ifndef MAINFUNCTIONS_H
#define MAINFUNCTIONS_H
char *writeOutFile(char *outGenFile, int length, int genI);
char *writeOutFilePNG(char *outGenFile, int length, int genI);
void help();
int isInterger(char *string);
int nextArgumentIsNotFlag(char *arg);
int noRequiredArguments(int outgenFlagUsed, int inputFlagUsed);
int makeNewGeneration(int **arr, int **newArr, int r, int c, int genI, char *outGenFile, int length, FILE *out, int *makeGen);
void freeAll(int **arr, int **newArr, int r, int c, int *makeGen, char *outGenFile);
void copyArrayToNewArray(int r, int c, int **arr, int **newArr);
#endif