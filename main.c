#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char get_char(char *arr, int i, int j, int row_length)
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

int range_rand(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

void cross(char *population, int row_length, char *best)
{
    int counter = 0;
    int number_of_best = strlen(best) / row_length;
    int best_index = range_rand(0, number_of_best - 1) * row_length;
    char *random_best = &best[best_index];
    for (size_t i = 0; i < strlen(population); i++)
    {
        if (counter == row_length)
        {
            best_index = range_rand(0, number_of_best - 1) * row_length;
            random_best = &best[best_index];
            counter = 0;
        }

        population[i] = random_best[counter];
        counter += 1;
    }
    char x = population[0];
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
    char *best = malloc(number_of_bytes * BEST);

    float **score = malloc(sizeof(float *) * POP);

    for (int i = 0; i < number_of_bytes * POP; i++)
    {
        population[i] = '0';
    }

    for (int i = 0; i < number_of_bytes * BEST; i++)
    {
        best[i] = 'A';
    }

    for (size_t i = 0; i < POP; i++)
    {
        score[i] = malloc(sizeof(float) * 2);
        score[i][0] = 0.0;
        score[i][1] = 0.0;
    }

    printf("Begining cycles");
    for (int cycle = 0; cycle < CYCLES; cycle++)
    {
        cross(population, number_of_bytes, best);
    }

    exit(0);
}