#include "tree.h"
#include "type.h"

char *t_integer = "Integer";
char *t_real = "Real";
char *t_string = "String";
char *t_void = "void";
char *t_auto = "auto";

int deduce_func_type(tree* func, char **type)
{
  // TODO
  *type = t_auto;
  return TYPE_AUTO;
}

int deduce_expr_type(tree* expr, tree* parent)
{
}

