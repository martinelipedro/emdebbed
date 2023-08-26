#ifndef EMDEBBED_VISITOR_H
#define EMDEBBED_VISITOR_H

#include "ast.h"

typedef struct STRUCT_TYPE__VISITOR
{
    

} visitor_T;

ast_T* visitor_visit(ast_T* node);
ast_T* visitor_visit_compound(ast_T* node);
ast_T* visitor_visit_string(ast_T* node);
ast_T* visitor_visit_function_call(ast_T* node);

#endif