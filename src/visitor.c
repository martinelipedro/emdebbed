#include "include/visitor.h"

#include <string.h>
#include <stdio.h>
#include "include/token.h"

void builtin_print(visitor_T* visitor, ast_compound_T* arguments)
{
    for (int i = 0; i < arguments->len; ++i)
    {
        ast_T* node = visitor_visit(visitor, ((ast_T*)arguments->data[i]));

        switch (node->type)
        {
            case AST_STRING: printf("%s\n", node->value.string); break;
            case AST_INTEGER: printf("%d\n", node->value.integer->value); break;
        }
    }
}

visitor_T* init_visitor()
{
    visitor_T* visitor = malloc(sizeof(visitor_T));

    visitor->global_context = init_context();

    return visitor;
}

ast_T* visitor_visit(visitor_T* visitor, ast_T* node)
{
    switch (node->type)
    {
        case AST_COMPOUND: return visitor_visit_compound(visitor, node);
        case AST_STRING: return visitor_visit_string(visitor, node);
        case AST_FUNCTION_CALL: return visitor_visit_function_call(visitor, node);
        case AST_VARIABLE_DEFINITION: return visitor_visit_variable_definition(visitor, node);
        case AST_VARIABLE: return visitor_visit_variable(visitor, node);
        case AST_BINARY_EXPR: return visitor_visit_binary_expr(visitor, node);
        case AST_INTEGER: return visitor_visit_integer(visitor, node);
        case AST_NOOP: return node;
    }
}

ast_T* visitor_visit_compound(visitor_T* visitor, ast_T* node)
{
    for (size_t i = 0; i < node->value.compound->len; ++i)
    {
        visitor_visit(visitor, node->value.compound->data[i]);
    }

    return node;
}

ast_T* visitor_visit_string(visitor_T* visitor, ast_T* node)
{
    return node;
}

ast_T* visitor_visit_function_call(visitor_T* visitor, ast_T* node)
{


    if (strcmp(node->value.function_call->name, "print") == 0)
    {
        builtin_print(visitor, node->value.function_call->arguments);
    }
    
    return node;
}

ast_T* visitor_visit_variable_definition(visitor_T* visitor, ast_T* node)
{
    context_set_variable(
        visitor->global_context, node->value.variable_definition->name,
        visitor_visit(visitor, node->value.variable_definition->value)
    );
}

ast_T* visitor_visit_variable(visitor_T* visitor, ast_T* node)
{
    return visitor_visit(visitor, context_get_variable(visitor->global_context, node->value.variable->name));
}

ast_T* visitor_visit_integer(visitor_T* visitor, ast_T* node)
{
    return node;
}

ast_T* visitor_visit_binary_expr(visitor_T* visitor, ast_T* node)
{
    switch (node->value.binary_expr->operator)
    {
        case TOK_PLUS:
        {
            ast_T* result = init_ast(AST_INTEGER);
            result->value.integer->value = 
                visitor_visit(visitor, node->value.binary_expr->lhs)->value.integer->value + \
                visitor_visit(visitor, node->value.binary_expr->rhs)->value.integer->value;
            
            return result;
            break;
        }
        case TOK_MINUS:
        {
            ast_T* result = init_ast(AST_INTEGER);
            result->value.integer->value = 
                visitor_visit(visitor, node->value.binary_expr->lhs)->value.integer->value - \
                visitor_visit(visitor, node->value.binary_expr->rhs)->value.integer->value;
            
            return result;
            break;
        }
        case TOK_STAR:
        {
            ast_T* result = init_ast(AST_INTEGER);
            result->value.integer->value = 
                visitor_visit(visitor, node->value.binary_expr->lhs)->value.integer->value * \
                visitor_visit(visitor, node->value.binary_expr->rhs)->value.integer->value;
            
            return result;
            break;
        }
        case TOK_SLASH:
        {
            ast_T* result = init_ast(AST_INTEGER);
            result->value.integer->value = 
                visitor_visit(visitor, node->value.binary_expr->lhs)->value.integer->value / \
                visitor_visit(visitor, node->value.binary_expr->rhs)->value.integer->value;
            
            return result;
            break;
        }
        case TOK_GREATER:
        {
            ast_T* result = init_ast(AST_INTEGER);
            result->value.integer->value = 
                visitor_visit(visitor, node->value.binary_expr->lhs)->value.integer->value > \
                visitor_visit(visitor, node->value.binary_expr->rhs)->value.integer->value;
            
            return result;
            break;
        }
        case TOK_LESSER:
        {
            ast_T* result = init_ast(AST_INTEGER);
            result->value.integer->value = 
                visitor_visit(visitor, node->value.binary_expr->lhs)->value.integer->value < \
                visitor_visit(visitor, node->value.binary_expr->rhs)->value.integer->value;
            
            return result;
            break;
        }
        case TOK_EQUALS_EQUALS:
        {
            ast_T* result = init_ast(AST_INTEGER);
            result->value.integer->value = 
                visitor_visit(visitor, node->value.binary_expr->lhs)->value.integer->value == \
                visitor_visit(visitor, node->value.binary_expr->rhs)->value.integer->value;
            
            return result;
            break;
        }
        case TOK_OR:
        {
            ast_T* result = init_ast(AST_INTEGER);
            result->value.integer->value = 
                visitor_visit(visitor, node->value.binary_expr->lhs)->value.integer->value || \
                visitor_visit(visitor, node->value.binary_expr->rhs)->value.integer->value;
            
            return result;
            break;
        }
        case TOK_AND:
        {
            ast_T* result = init_ast(AST_INTEGER);
            result->value.integer->value = 
                visitor_visit(visitor, node->value.binary_expr->lhs)->value.integer->value && \
                visitor_visit(visitor, node->value.binary_expr->rhs)->value.integer->value;
            
            return result;
            break;
        }
    }
}