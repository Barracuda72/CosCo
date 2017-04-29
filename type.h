#ifndef __TYPE_H__
#define __TYPE_H__

#include "tree.h"

/*
 * Type deduction
 */

/*
 * Types
 */
enum
{
  TYPE_INTEGER = 4000,
  TYPE_REAL    = 4001,
  TYPE_STRING  = 4002,
  TYPE_CUSTOM  = 4003,
  TYPE_VOID    = 4004,
  TYPE_AUTO    = 4005,
};

/*
 * Deduce functions
 */
int deduce_func_type(tree* func, tree* parent, char **type);
int deduce_expr_type(tree* expr, tree* parent, char** type);
int deduce_type_for_stmt(tree* list, tree* parent, char** type, int* retn_found);
int deduce_type_for_stmt_list(tree* list, tree* parent, char** type, int* retn_found);

#endif // __TYPE_H__
