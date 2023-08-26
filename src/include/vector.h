#ifndef EMDEBBED_VECTOR_H
#define EMDEBBED_VECTOR_H

#include <stdlib.h>


typedef struct STRUCT_TYPE__VECTOR
{
    void** data;
    size_t element_size;
    size_t len;
    size_t size;

} vector_T;

vector_T* init_vector(size_t element_size);

void vector_push(vector_T* vector, void* element);
void vector_pop(vector_T* vector);
void* vector_get(vector_T* vector, size_t index);

#endif