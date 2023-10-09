#include "include/context.h"

context_T* init_context()
{
    context_T* context = malloc(sizeof(context_T));

    context->variables = init_map(sizeof(ast_T*));
    context->functions = init_map(sizeof(ast_T*));

    return context;
}

void context_set_variable(context_T* context, char* name, ast_T* value)
{
    if (context_variable_exists(context, name))
    {
        map_change_value(context->variables, name, value);
        return;
    }

    map_add(context->variables, name, value);
}

int context_variable_exists(context_T* context, char* name)
{
    return map_key_exists(context->variables, name);
}

ast_T* context_get_variable(context_T* context, char* name)
{
    return map_get(context->variables, name);
}