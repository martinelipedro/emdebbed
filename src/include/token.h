#ifndef EMDEBBED_TOKEN_H
#define EMDEBBED_TOKEN_H

typedef struct STRUCT_TYPE___TOKEN
{
    int type;
    char* value;

} token_T; // STRUCT_TYPE__TOKEN

token_T* init_token(int type, char* value);

#endif