#ifndef EMDEBBED_AST_H
#define EMDEBBED_AST_H

#include "vector.h"

struct STRUCT_TYPE__AST;

enum ENUM__AST_TYPE
{
    AST_NOOP,
    AST_COMPOUND,
    AST_VARIABLE_DEFINITION,
    AST_STRING,
};

typedef vector_T ast_compound_T;
typedef char ast_string_T;
typedef struct STRUCT_TYPE__AST_TYPE__VARIABLE_DEFINITION
{
    char* name;
    struct STRUCT_TYPE__AST* value;

} ast_variable_definition_T;

typedef struct STRUCT_TYPE__AST
{
    int type;
    union 
    {
        ast_compound_T* compound;
        ast_variable_definition_T* variable_definition;
        ast_string_T* string;
    } value;

} ast_T;

ast_T* init_ast(int type);

#endif