#include "include/ast.h"

#define ID_MAX_SIZE 30

ast_T* init_ast(int type)
{
    ast_T* ast = malloc(sizeof(ast_T));
    ast->type = type;

    switch (type)
    {
        case AST_COMPOUND:
        {
            ast->value.compound = init_vector(sizeof(ast_T*));
            break;
        }
        case AST_VARIABLE_DEFINITION:
        {
            ast->value.variable_definition = malloc(sizeof(ast_variable_definition_T));
            ast->value.variable_definition->name = malloc(sizeof(char));
            ast->value.variable_definition->value = (void*)0;
            break;
        }
        case AST_STRING:
        {
            ast->value.string = calloc(50, sizeof(char));
            break;
        }
        case AST_FUNCTION_CALL:
        {
            ast->value.function_call = malloc(sizeof(ast_function_call_T));
            ast->value.function_call->arguments = init_vector(sizeof(ast_T*));
            ast->value.function_call->name = malloc(ID_MAX_SIZE * sizeof(char));
            break;
        }
        case AST_VARIABLE:
        {
            ast->value.variable = malloc(sizeof(ast_variable_T));
            ast->value.variable->name = calloc(ID_MAX_SIZE, sizeof(char));
            break;
        }
        case AST_INTEGER:
        {
            ast->value.integer = malloc(sizeof(ast_int_T));
            ast->value.integer->literal = calloc(10, sizeof(char));
            ast->value.integer->value = 0;
            break;
        }
        case AST_BINARY_EXPR:
        {
            ast->value.binary_expr = malloc(sizeof(ast_bin_expr_T));
            ast->value.binary_expr->lhs = (void*)0;
            ast->value.binary_expr->lhs = (void*)0;
            ast->value.binary_expr->operator = -1;
            break;
        }
        case AST_IF_STATEMENT:
        {
            ast->value.if_stmt = malloc(sizeof(ast_if_stmt_T));
            ast->value.if_stmt->expr = (void*)0;
            ast->value.if_stmt->statements = (void*)0;
            break;
        }
        case AST_WHILE_STATEMENT:
        {
            ast->value.while_stmt = malloc(sizeof(ast_if_stmt_T));
            ast->value.while_stmt->expr = (void*)0;
            ast->value.while_stmt->statements = (void*)0;
            break;
        }
        case AST_FUNCTION_DEFINITION:
        {
            ast->value.function_definition = malloc(sizeof(ast_funcdef_T));
            ast->value.function_definition->body = (void*)0;
            ast->value.function_definition->name = calloc(ID_MAX_SIZE, sizeof(char));
            ast->value.function_definition->return_value = (void*)0;
            ast->value.function_definition->arguments = init_vector(ID_MAX_SIZE * sizeof(char));
            break; 
        } 
    }

    return ast;
}