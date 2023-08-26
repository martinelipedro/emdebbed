#ifndef EMDEBBED_PARSER_H
#define EMDEBBED_PARSER_H

#include "lexer.h"
#include "ast.h"

typedef struct STRUCT_TYPE__PARSER
{
    lexer_T* lexer;
    token_T* current_token;
    token_T* last_token;

} parser_T;

parser_T* init_parser(lexer_T* lexer);

token_T* parser_eat(parser_T* parser, int token);
void parser_advance(parser_T* parser);

ast_T* parser_parse_compound(parser_T* parser);
ast_T* parser_parse_statements(parser_T* parser);
ast_T* parser_parse_id(parser_T* parser);
ast_T* parser_parse_variable_definition(parser_T* parser);
ast_T* parser_parse_function_call(parser_T* parser);
ast_T* parser_parse_string(parser_T* parser);
ast_T* parser_parse_variable(parser_T* parser);

ast_T* parser_parse_expr(parser_T* parser);

ast_T* parser_parse_arith_expr(parser_T* parser);
ast_T* parser_parse_term(parser_T* parser);
ast_T* parser_parse_factor(parser_T* parser);

#endif