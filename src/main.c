#include "include/lexer.h"
#include "include/vector.h"
#include "include/parser.h"
#include "include/visitor.h"

#include <stdio.h>

#define to_ast(node) ((ast_T*)node)

int main()
{
    lexer_T* lexer = init_lexer("print(\"fgdjkgmd, \");");
    parser_T* parser = init_parser(lexer);

    ast_T* root = parser_parse_compound(parser);
    visitor_visit(root);
}