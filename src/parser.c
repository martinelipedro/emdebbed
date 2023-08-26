#include "include/parser.h"
#include <stdlib.h>
#include <stdio.h>

#include <string.h>

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
        default: return init_ast(AST_NOOP);
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