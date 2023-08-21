#include "include/token.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

token_T* init_token(int type, char* value)
{
    token_T* token = malloc(sizeof(token_T));

    token->type = type;
    token->value = value;

    return token;
}

const char* token_get_string_repr(token_T* token)
{
    char* buffer = malloc((strlen(token->value) + strlen("( : )") + 4) * sizeof(char));
    (void)!sprintf(buffer, "(%d: %s)\n", token->type, token->value);
    return buffer;
}

void token_print_repr_to_terminal(token_T* token)
{
    printf("%s", token_get_string_repr(token));
}