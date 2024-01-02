#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// encryption

#define MULN 2
#define ADDN 10
int encrypt_char(char c, int k)
{
    return (c ^ (char)k) * MULN + ADDN;
}

// files

#define EXPECT_FILE_SIZE 128
const char *load_file_to_buffer(const char *filename)
{
    FILE *infile = fopen(filename, "r");
    if (infile == NULL)
    {
        fprintf(stderr, "%s couldn't be opened!\n", filename);
        return NULL;
    }
    char *buffer = (char *)malloc(sizeof(char) * EXPECT_FILE_SIZE);
    memset(buffer, '\0', EXPECT_FILE_SIZE * sizeof(char));
    fread(buffer, sizeof(char), EXPECT_FILE_SIZE, infile);
    fclose(infile);
    return (const char *)buffer;
}

const char *get_file_ext(const char *filename)
{
    int i = strlen(filename) - 1;
    int hasExt = 0;
    for (; i >= 0; i--)
    {
        if (filename[i] == '.')
        {
            hasExt = 1;
            break;
        }
    }
    return hasExt ? filename + i + 1 : "";
}

//array functions

void print_intarr_elems(int *array, int length)
{
    printf("%d",array[0]);
    for(int i=1; i<length; ++i)
        printf(" %d",array[i]);
    printf("\n");
    return;
}

void print_fltarr_elems(float *array, int length)
{
    printf("%f",array[0]);
    for(int i=1; i<length; ++i)
        printf(" %f",array[i]);
    printf("\n");
    return;
}