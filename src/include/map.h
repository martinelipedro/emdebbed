#ifndef EMDEBBED_MAP_H
#define EMDEBBED_MAP_H

#include "vector.h"

#define KEY_STRING_SIZE 20

typedef struct MAP_STRUCT
{
    vector_T* keys;
    vector_T* data;
    size_t len;

} map_T;

map_T* init_map(size_t data_size);
void map_add(map_T* map, char* key, void* value);
void map_change_value(map_T* map, char* key, void* value);
void* map_get(map_T* map, char* key);
int map_key_exists(map_T* map, char* key);
int map_is_empty(map_T* map, char* key);

#endif