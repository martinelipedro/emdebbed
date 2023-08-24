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
            ast->value.string = malloc(50 * sizeof(char));
            break;
        }
    }

    return ast;
}