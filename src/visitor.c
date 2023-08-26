#include "include/visitor.h"

#include <string.h>
#include <stdio.h>

void builtin_print(ast_compound_T* arguments)
{
    for (int i = 0; i < arguments->len; ++i)
    {
        printf("%s\n", ((ast_T*)(arguments->data[i]))->value.string);
    }
}

ast_T* visitor_visit(ast_T* node)
{
    switch (node->type)
    {
        case AST_COMPOUND: return visitor_visit_compound(node);
        case AST_STRING: return visitor_visit_string(node);
        case AST_FUNCTION_CALL: return visitor_visit_function_call(node);
        case AST_NOOP: return node;
    }
}

ast_T* visitor_visit_compound(ast_T* node)
{
    for (size_t i = 0; i < node->value.compound->len; ++i)
    {
        visitor_visit(node->value.compound->data[i]);
    }

    return node;
}

ast_T* visitor_visit_string(ast_T* node)
{

}

ast_T* visitor_visit_function_call(ast_T* node)
{


    if (strcmp(node->value.function_call->name, "print") == 0)
    {
        builtin_print(node->value.function_call->arguments);
    }
    
    return node;
}