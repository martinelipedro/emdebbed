#include "include/visitor.h"
#include "include/parser.h"
#include "include/file.h"
#include <stdio.h>

#define to_ast(node) ((ast_T*)node)

int main()
{
    lexer_T* lexer = init_lexer(read_from_file("test.emb"));
    parser_T* parser = init_parser(lexer);
    visitor_T* visitor = init_visitor();
    ast_T* root = parser_parse_compound(parser); 

    // printf("%s", to_ast(root->value.compound->data[1])->value.function_call->name);

    visitor_visit(visitor, root);
    
}