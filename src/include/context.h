#ifndef EMDEBBED_CONTEXT_H
#define EMDEBBED_CONTEXT_H

#include "ast.h"
#include "map.h"

typedef struct STRUCT_TYPE__CONTEXT
{
    map_T* variables;

} context_T;

context_T* init_context();

void context_set_variable(context_T* context, char* name, ast_T* value);
int context_variable_exists(context_T* context, char* name);
ast_T* context_get_variable(context_T* context, char* name);

#endif