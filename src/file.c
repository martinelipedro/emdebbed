#include "include/file.h"

#include <stdlib.h>
#include <stdio.h>

const char* read_from_file(const char* filepath)
{
    char* buffer = (void*)0;
    long lenght;

    FILE* file = fopen(filepath, "rb");
    if (file)
    {
        fseek(file, 0, SEEK_END);
        lenght = ftell(file);
        fseek(file, 0, SEEK_SET);

        buffer = calloc(lenght, lenght);
        if (buffer)
        {
            (void)!fread(buffer, 1, lenght, file);
        }

        fclose(file);
        return buffer;
    }

    printf("File not found or error while reading file: %s\n", filepath);
    exit(1);
}