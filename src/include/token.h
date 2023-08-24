#ifndef EMDEBBED_TOKEN_H
#define EMDEBBED_TOKEN_H

enum ENUM__TOKEN_TYPE
{
    TOK_EOF = -1,
    TOK_ID,
    TOK_EQUALS,
    TOK_STRING,
    TOK_SEMICOLON,
};

typedef struct STRUCT_TYPE__TOKEN
{
    int type;
    char* value;

} token_T; // STRUCT_TYPE__TOKEN

token_T* init_token(int type, char* value);

const char* token_get_string_repr(token_T* token);
void token_print_repr_to_terminal(token_T* token);

#endif