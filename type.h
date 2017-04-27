#ifndef __TYPE_H__
#define __TYPE_H__

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

int deduce_func_type(tree* func, char **type);
int deduce_expr_type(tree* expr, tree* parent);

#endif // __TYPE_H__
