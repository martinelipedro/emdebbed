#ifndef EMDEBBED_VISITOR_H
#define EMDEBBED_VISITOR_H

#include "ast.h"
#include "context.h"

typedef struct STRUCT_TYPE__VISITOR
{
    context_T* global_context;

} visitor_T;

visitor_T* init_visitor();

ast_T* visitor_visit(visitor_T* visitor, ast_T* node);
ast_T* visitor_visit_compound(visitor_T* visitor, ast_T* node);
ast_T* visitor_visit_string(visitor_T* visitor, ast_T* node);
ast_T* visitor_visit_function_call(visitor_T* visitor, ast_T* node);
ast_T* visitor_visit_variable_definition(visitor_T* visitor, ast_T* node);
ast_T* visitor_visit_variable(visitor_T* visitor, ast_T* node);

#endif