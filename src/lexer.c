#include "include/lexer.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

lexer_T* init_lexer(const char* source_code)
{
    lexer_T* lexer = malloc(sizeof(lexer_T));

    lexer->source = source_code;
    lexer->current_index = 0;
    lexer->current_char = source_code[0];

    return lexer;
}

void lexer_advance(lexer_T* lexer)
{
    if (lexer->current_index >= strlen(lexer->source))
    {
        return;
    }

    lexer->current_index++;
    lexer->current_char = lexer->source[lexer->current_index];
}

token_T* lexer_get_next_token(lexer_T* lexer)
{
    while (lexer->current_char == ' ' || lexer->current_char == '\n' || lexer->current_char == '\r')
    {
        lexer_advance(lexer);
    }

    if (isalpha(lexer->current_char)  || lexer->current_char == '_')
        return lexer_collect_id(lexer);
    
    if (isdigit(lexer->current_char))
        return lexer_collect_number(lexer);


    switch (lexer->current_char)
    {
        case '"': return lexer_collect_string(lexer); 
        case '=':
        {
            lexer_advance(lexer);
            if (lexer->current_char == '=')
            {
                lexer_advance(lexer);
                return init_token(TOK_EQUALS_EQUALS, "==");
            }
            return init_token(TOK_EQUALS, "=");
        }
        case ';': lexer_advance(lexer); return init_token(TOK_SEMICOLON, ";");
        case '(': lexer_advance(lexer); return init_token(TOK_LPAREN, "(");
        case ')': lexer_advance(lexer); return init_token(TOK_RPAREN, ")");
        case ',': lexer_advance(lexer); return init_token(TOK_COMMA, ",");
        case '*': lexer_advance(lexer); return init_token(TOK_STAR, "*");
        case '/': lexer_advance(lexer); return init_token(TOK_SLASH, "/");
        case '+': lexer_advance(lexer); return init_token(TOK_PLUS, "+");
        case '-': lexer_advance(lexer); return init_token(TOK_MINUS, "-");
        case '>': lexer_advance(lexer); return init_token(TOK_GREATER, ">");
        case '<': lexer_advance(lexer); return init_token(TOK_LESSER, "<");



        default: return init_token(TOK_EOF, 0);
    }
}

token_T* lexer_collect_id(lexer_T* lexer)
{
    char* buffer = calloc(1, sizeof(char));

    while (isalnum(lexer->current_char) || lexer->current_char == '_')
    {
        buffer = realloc(buffer, (strlen(buffer) + 2) * sizeof(char));
        strcat(buffer, (char[]){lexer->current_char, 0});
        lexer_advance(lexer);
    }

    return init_token(TOK_ID, buffer);
}

token_T* lexer_collect_string(lexer_T* lexer)
{
    char* buffer = calloc(1, sizeof(char));

    lexer_advance(lexer);
    while (lexer->current_char != '"')
    {
        buffer = realloc(buffer, (strlen(buffer) + 2) * sizeof(char));
        strcat(buffer, (char[]){lexer->current_char, 0});
        lexer_advance(lexer);
    }
    lexer_advance(lexer);

    return init_token(TOK_STRING, buffer);
}

token_T* lexer_collect_number(lexer_T* lexer)
{
    char* buffer = calloc(1, sizeof(char));

    while (isdigit(lexer->current_char))
    {
        buffer = realloc(buffer, (strlen(buffer) + 2) * sizeof(char));
        strcat(buffer, (char[]){lexer->current_char, 0});
        lexer_advance(lexer);
    }

    return init_token(TOK_INT, buffer);
}