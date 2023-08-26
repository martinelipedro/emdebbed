#ifndef EMDEBBED_AST_H
#define EMDEBBED_AST_H

#include "vector.h"

struct STRUCT_TYPE__AST;

enum ENUM__AST_TYPE
{
    AST_NOOP,
    AST_COMPOUND,
    AST_VARIABLE_DEFINITION,
    AST_VARIABLE,
    AST_FUNCTION_CALL,
    AST_STRING,
    AST_INTEGER,
    AST_BINARY_EXPR,
};

typedef vector_T ast_compound_T;
typedef char ast_string_T;
typedef struct STRUCT_TYPE__AST_TYPE__VARIABLE_DEFINITION
{
    char* name;
    struct STRUCT_TYPE__AST* value;

} ast_variable_definition_T;

typedef struct STRUCT_TYPE__AST_TYPE__FUNCTION_CALL
{
    char* name;
    ast_compound_T* arguments;
} ast_function_call_T;

typedef struct STRUCT_TYPE__AST_TYPE__VARIABLE
{
    char* name;
} ast_variable_T;

typedef struct STRUCT_TYPE__AST_TYPE__INTEGER
{
    char* literal;
    int value;

} ast_int_T;

typedef struct STRUCT_TYPE__AST_TYPE_BINARY_EXPR
{
    struct STRUCT_TYPE__AST* lhs;
    struct STRUCT_TYPE__AST* rhs;
    int operator;

} ast_bin_expr_T;

typedef struct STRUCT_TYPE__AST
{
    int type;
    union 
    {
        ast_compound_T* compound;
        ast_variable_definition_T* variable_definition;
        ast_function_call_T* function_call;
        ast_string_T* string;
        ast_variable_T* variable;
        ast_int_T* integer;
        ast_bin_expr_T* binary_expr;
    } value;

} ast_T;

ast_T* init_ast(int type);

#endif