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
    AST_UNARY_EXPR,
    AST_IF_STATEMENT,
    AST_WHILE_STATEMENT,
    AST_FUNCTION_DEFINITION,
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

typedef struct STRUCT_TYPE__AST_TYPE_UNARY_EXPR
{
    int operator;
    struct STRUCT_TYPE__AST *lhs;
} ast_un_expr_T;

typedef struct STRUCT_TYPE__AST_TYPE_IF_STATEMENT
{
    struct STRUCT_TYPE__AST* expr;
    struct STRUCT_TYPE__AST* statements;

} ast_if_stmt_T;

typedef struct STRUCT_TYPE_AST_TYPE_WHILE_STATEMENT
{
    struct STRUCT_TYPE__AST* expr;
    struct STRUCT_TYPE__AST* statements;

} ast_while_stmt_T;

typedef struct STRUCT_TYPE__AST_TYPE_FUNCTION_DEFINITION
{
    char* name;
    vector_T* arguments;
    struct STRUCT_TYPE__AST*  body;
    struct STRUCT_TYPE__AST* return_value;

} ast_funcdef_T;

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
        ast_if_stmt_T* if_stmt;
        ast_while_stmt_T* while_stmt;
        ast_un_expr_T* unary_expr;
        ast_funcdef_T* function_definition;
    } value;

} ast_T;

ast_T* init_ast(int type);

#endif