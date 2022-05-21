#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// void cross(int rows, int cols, char *population) {
//     printf("Cross...");
//     for (int i = 0; i < rows; i++)
//     {
//         for (int j = 0; j < cols; j++)
//         {
//             printf("%d ",i);
//             printf("%d \n",j);
//         }

//     }
// }

char index(char *arr, int i, int j, int row_length)
{
    int pos = (row_length * i) + j;
    return arr[pos];
}

char *read(char *path)
{
    FILE *fp = fopen(path, "r");

    if (fp == NULL)
    {
        fprintf(stderr, "Can't open file: '%s'", path);
        exit(1);
    }

    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);

    char *content = malloc(sizeof(char) * size);
    printf("Size: '%d'\n", size);
    fseek(fp, 0, SEEK_SET);

    fread(content, 1, size, fp);

    fclose(fp);

    return content;
}

int main(int argc, char *argv[])
{
    const int POP = 100;
    const int BEST = 10;
    const int CYCLES = 10000;

    char *file_name = argv[1];

    char *bytes = read(file_name);
    int number_of_bytes = strlen(bytes);

    char *population = malloc(number_of_bytes * POP);
    char *best = malloc(BEST);

    float **score = malloc(sizeof(float *) * POP);

    for (int i = 0; i < POP; i++)
    {
        population[i] = '0';

        score[i] = malloc(sizeof(float) * 2);
        score[i][0] = 0.0;
        score[i][1] = 0.0;
    }

    for (int i = 0; i < BEST; i++)
    {
        best[i] = 0;
    }

    printf("Begining cycles");
    for (int cycle = 0; cycle < CYCLES; cycle++)
    {
        // cross(POP, size, *population);
    }

    exit(0);
}