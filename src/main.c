#include "include/lexer.h"
#include "include/vector.h"
#include "include/parser.h"

#include <stdio.h>

int main()
{
    lexer_T* lexer = init_lexer("test = \"other\";;");
    parser_T* parser = init_parser(lexer);

    ast_T* root = parser_parse_compound(parser);

    printf("%s", ((ast_T*)root->value.compound->data[0])->value.variable_definition->value->value.string);
}