#include "include/parser.h"
#include <stdlib.h>
#include <stdio.h>

#include <string.h>

int h_is_end_expr_tok(int type)
{
    if (type == TOK_SEMICOLON || type == TOK_RPAREN)
    {
        return 1;
    }

    return 0;
}

#define ctok printf("%d", parser->current_token->type);

parser_T* init_parser(lexer_T* lexer)
{
    parser_T* parser = malloc(sizeof(lexer_T));

    parser->lexer = lexer;
    parser->current_token = lexer_get_next_token(parser->lexer);
    parser->last_token = parser->current_token;

    return parser;
}

token_T* parser_eat(parser_T* parser, int token)
{
    token_T* current_token = parser->current_token;

    if (current_token->type != token)
    {
        printf("Unexpected Token %d, the expected was: %d", current_token->type, token);
        exit(1);
    }

    parser_advance(parser);

    return current_token;
}

void parser_advance(parser_T* parser)
{
    parser->last_token = parser->current_token;
    parser->current_token = lexer_get_next_token(parser->lexer);
}

ast_T* parser_parse_compound(parser_T* parser)
{
    ast_T* ast = init_ast(AST_COMPOUND);

    vector_push(ast->value.compound, (void*)parser_parse_statements(parser));

    while (parser->current_token->type == TOK_SEMICOLON)
    {
        parser_eat(parser, TOK_SEMICOLON);
        vector_push(ast->value.compound, (void*)parser_parse_statements(parser));
    }

    return ast;
}

ast_T* parser_parse_statements(parser_T* parser)
{

    switch (parser->current_token->type)
    {
        case TOK_ID: return parser_parse_id(parser); break;
        case TOK_STRING: return parser_parse_string(parser); break;
        case TOK_INT: return parser_parse_expr(parser); break;
    }

    return init_ast(AST_NOOP);
}

ast_T* parser_parse_id(parser_T* parser)
{
    parser_advance(parser);

    switch (parser->current_token->type)
    {
        case TOK_EQUALS: return parser_parse_variable_definition(parser);
        case TOK_LPAREN: return parser_parse_function_call(parser);
        default: return parser_parse_expr(parser);
    }
}

ast_T* parser_parse_variable_definition(parser_T* parser)
{
    ast_T* ast = init_ast(AST_VARIABLE_DEFINITION);
    char* variable_name = parser->last_token->value;

    parser_eat(parser, TOK_EQUALS);


    ast->value.variable_definition->name = variable_name;
    ast->value.variable_definition->value = parser_parse_statements(parser);

    return ast;
}

ast_T* parser_parse_function_call(parser_T* parser)
{
    ast_T* ast = init_ast(AST_FUNCTION_CALL);
    ast->value.function_call->name = parser->last_token->value;

    parser_eat(parser, TOK_LPAREN);

    if (parser->current_token->type == TOK_RPAREN)
    {
        parser_eat(parser, TOK_RPAREN);
        return ast;
    }

    vector_push(ast->value.function_call->arguments, (void*)parser_parse_statements(parser));
    while (parser->current_token->type == TOK_COMMA)
    {
        parser_eat(parser, TOK_COMMA);
        vector_push(ast->value.function_call->arguments, (void*)parser_parse_statements(parser));
    }
    parser_eat(parser, TOK_RPAREN);

    return ast;
}

ast_T* parser_parse_string(parser_T* parser)
{
    ast_T* ast = init_ast(AST_STRING);

    ast->value.string = parser_eat(parser, TOK_STRING)->value;

    return ast;
}

ast_T* parser_parse_variable(parser_T* parser)
{
    ast_T* ast = init_ast(AST_VARIABLE);

    ast->value.variable->name = parser->last_token->value;

    return ast;
}

ast_T* parser_parse_expr(parser_T* parser)
{
    ast_T* left, *right;
    left = parser_parse_compare_expr(parser);

    token_T* token = parser->current_token;

    if (h_is_end_expr_tok(token->type))
    {
        return left;
    }

    while (token->type == TOK_OR || token->type == TOK_AND)
    {
        parser_advance(parser);

        right = parser_parse_compare_expr(parser);
        ast_T* new_left = init_ast(AST_BINARY_EXPR);
        new_left->value.binary_expr->lhs = left;
        new_left->value.binary_expr->rhs = right;
        new_left->value.binary_expr->operator = token->type;
        left = new_left;

        token = parser->current_token;
        if (h_is_end_expr_tok(token->type)) break;
    }

    return left;
}

ast_T* parser_parse_compare_expr(parser_T* parser)
{
    ast_T* left, *right;
    left = parser_parse_arith_expr(parser);

    token_T* token = parser->current_token;

    if (token->type == TOK_SEMICOLON || token->type == TOK_RPAREN)
    {
        return left;
    }
    
    while (token->type == TOK_GREATER || token->type == TOK_LESSER || TOK_EQUALS_EQUALS)
    {
        parser_advance(parser);

        right = parser_parse_arith_expr(parser);
        ast_T* new_left = init_ast(AST_BINARY_EXPR);
        new_left->value.binary_expr->lhs = left;
        new_left->value.binary_expr->rhs = right;
        new_left->value.binary_expr->operator = token->type;
        left = new_left;

        token = parser->current_token;
        if (token->type == TOK_SEMICOLON || token->type == TOK_RPAREN) break;
    }

    return left;
}

ast_T* parser_parse_arith_expr(parser_T* parser)
{   
    ast_T* left, *right;
    left = parser_parse_term(parser);

    token_T* token = parser->current_token;


    if (token->type == TOK_SEMICOLON || token->type == TOK_RPAREN)
    {
        return left;
    }
    
    while (token->type == TOK_PLUS || token->type == TOK_MINUS)
    {
        parser_advance(parser);

        right = parser_parse_term(parser);
        ast_T* new_left = init_ast(AST_BINARY_EXPR);
        new_left->value.binary_expr->lhs = left;
        new_left->value.binary_expr->rhs = right;
        new_left->value.binary_expr->operator = token->type;
        left = new_left;

        token = parser->current_token;
        if (token->type == TOK_SEMICOLON || token->type == TOK_RPAREN) break;
    }

    return left;
}

ast_T* parser_parse_term(parser_T* parser)
{


    ast_T* left, *right;
    left = parser_parse_factor(parser);



    token_T* token = parser->current_token;


    if (token->type == TOK_SEMICOLON || token->type == TOK_RPAREN)
    {
        return left;
    }
    
    while (token->type == TOK_STAR || token->type == TOK_SLASH)
    {
        parser_advance(parser);

        right = parser_parse_factor(parser);
        ast_T* new_left = init_ast(AST_BINARY_EXPR);
        new_left->value.binary_expr->lhs = left;
        new_left->value.binary_expr->rhs = right;
        new_left->value.binary_expr->operator = token->type;
        left = new_left;

        token = parser->current_token;
        if (token->type == TOK_SEMICOLON || token->type == TOK_RPAREN) break;
    }

    return left;
}

ast_T* parser_parse_factor(parser_T* parser)
{
    token_T* token = parser->current_token;



    switch (token->type)
    {
        case TOK_INT:
        {
            ast_T* ast = init_ast(AST_INTEGER);
            ast->value.integer->literal = token->value;
            ast->value.integer->value = atoi(token->value);
            parser_eat(parser, TOK_INT);
            return ast;
        }
        default:
        {
            return parser_parse_variable(parser);
        }
    }
}