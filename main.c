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

void cross(size_t pop_size, size_t best_size, char *population[pop_size], char *best[best_size], int row_length)
{
    for (size_t i = 0; i < pop_size; i++)
    {
        char *speciment = population[i];
        int random_index = range_rand(0, best_size - 1);
        char *random_best = best[random_index];

        speciment = random_best;
    }
}

void mutate(size_t pop_size, char *population[pop_size], int width, int height)
{
    for (size_t i = 0; i < pop_size; i++)
    {
        char *speciment = population[i];

        int end_x = range_rand(1, width - 1);
        int end_y = range_rand(1, height - 1);

        int start_x = range_rand(1, width - end_x);
        int start_y = range_rand(1, height - end_y);

        int color = range_rand(0, 255);

        for (size_t x = 0; x < end_y + start_y; x++)
        {
            for (size_t y = 0; y < end_x + start_x; y++)
            {
                int index = (x * width + y);
                speciment[index] = (speciment[index] / 2) + (color / 2);
            }
        }
    }
}

void score(size_t pop_size, size_t bytes_size, char *population[pop_size], char *bytes, float scores[pop_size][2])
{
    for (size_t i = 0; i < pop_size; i++)
    {
        char *speciment = population[i];
        float value = 0;

        for (size_t j = 0; j < bytes_size; j++)
        {
            char byte = bytes[j];

            if (byte < speciment[j])
            {
                value += speciment[j] - byte;
            }
            else
            {
                value += byte - speciment[j];
            }
        }
        scores[i][0] = value;
        scores[i][1] = i;
    }
}

int main(int argc, char *argv[])
{
    const int POP = 100;
    const int BEST = 10;
    const int CYCLES = 10000;
    const int width = 400;
    const int height = 400;

    char *file_name = argv[1];

    char *bytes = read(file_name);
    int number_of_bytes = strlen(bytes);

    size_t pop_length = number_of_bytes * POP;
    size_t best_length = number_of_bytes * BEST;

    float scores[POP][2];
    char *population[POP];
    char *best[BEST];

    for (size_t i = 0; i < POP; i++)
    {
        population[i] = malloc(number_of_bytes);

        scores[i][0] = 0;
        scores[i][1] = (float)i;

        for (size_t j = 0; j < number_of_bytes; j++)
        {
            population[i][j] = 0;
        }
    }
    for (size_t i = 0; i < BEST; i++)
    {
        best[i] = malloc(number_of_bytes);
        for (size_t j = 0; j < number_of_bytes; j++)
        {
            best[i][j] = 0;
        }
    }

    printf("Begining cycles\n");
    for (int cycle = 0; cycle < CYCLES; cycle++)
    {
        cross(POP, BEST, population, best, number_of_bytes);
        mutate(POP, population, width, height);
        score(POP, number_of_bytes, population, bytes, scores);
    }

    exit(0);
}