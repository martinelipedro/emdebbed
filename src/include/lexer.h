#ifndef EMDEBBED_LEXER_H
#define EMDEBBED_LEXER_H

#include "token.h"

typedef struct STRUCT_TYPE__LEXER
{
    const char* source;
    unsigned int current_index;
    char current_char;

} lexer_T; // STRUCT_TYPE__LEXER

lexer_T* init_lexer(const char* source_code);

void lexer_advance(lexer_T* lexer);

token_T* lexer_get_next_token(lexer_T* lexer);
token_T* lexer_collect_id(lexer_T* lexer);
token_T* lexer_collect_string(lexer_T* lexer);
token_T* lexer_collect_number(lexer_T* lexer);


#endif