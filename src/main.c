#include "include/lexer.h"
#include "include/vector.h"
#include "include/parser.h"
#include "include/visitor.h"
#include <stdio.h>
#include "include/context.h"
#include "include/file.h"

#define to_ast(node) ((ast_T*)node)

int main()
{
    lexer_T* lexer = init_lexer(read_from_file("test.emb"));
    parser_T* parser = init_parser(lexer);
    visitor_T* visitor = init_visitor();
    ast_T* root = parser_parse_compound(parser);
    
    visitor_visit(visitor, root);
}