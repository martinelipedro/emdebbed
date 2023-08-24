#include "include/vector.h"

vector_T* init_vector(size_t element_size)
{
    vector_T* vector = malloc(sizeof(vector_T));

    vector->element_size = element_size;
    vector->size = 0;
    vector->len = 0;
    vector->data = (void*)0;

    return vector;
}

void vector_push(vector_T* vector, void* element)
{
    vector->len++;
    vector->size = vector->len * sizeof(vector->element_size);

    if (vector->len == 1)
    {
        vector->data = calloc(1, sizeof(vector->element_size));
        vector->data[0] = element;
        return;
    }

    vector->data = realloc(vector->data, vector->size);
    vector->data[vector->len - 1] = element;
}