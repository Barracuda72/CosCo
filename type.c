#include <assert.h>

#include "tree.h"
#include "type.h"

char *t_integer = "Integer";
char *t_real = "Real";
char *t_string = "String";
char *t_void = "void";
char *t_auto = "auto";

/*
 * Deduce type for function
 * It's type of return statements or void, if there aren't any
 */
int deduce_func_type(tree* func, tree* parent, char **type)
{
  int ret = TYPE_AUTO;
  int retn_found = 0;

  assert (func->type == NODE_FUNC_DEF);

  tree *stmts = func->right;

  if (stmts != NULL) /* No statements -> void function */
    ret = deduce_type_for_stmt(stmts, parent, type, &retn_found);

  if (ret == TYPE_AUTO) /* Failed to deduce type */
  {
    if (retn_found == 0) /* No return statements found -> void */
    {
      *type = t_void;
      ret = TYPE_VOID;
    } else {
      *type = t_auto;
    }
  }

  return ret;
}

/*
 * Select most powerful from provided two types
 */
int mix_types(int r1, char *t1, int r2, char *t2, char** type)
{
  /* AUTO is strongliest */
  if (r1 == TYPE_AUTO)
  {
    *type = t1;
    return r1;
  }

  if (r2 == TYPE_AUTO)
  {
    *type = t2;
    return r2;
  }

  /* CUSTOM is second strongliest */
  if (r1 == TYPE_CUSTOM)
  {
    *type = t1;
    return r1;
  }

  if (r2 == TYPE_CUSTOM)
  {
    *type = t2;
    return r2;
  }

  /* String is next */
  if (r1 == TYPE_STRING)
  {
    *type = t1;
    return r1;
  }

  if (r2 == TYPE_STRING)
  {
    *type = t2;
    return r2;
  }

  /* Then Real */
  if (r1 == TYPE_REAL)
  {
    *type = t1;
    return r1;
  }

  if (r2 == TYPE_REAL)
  {
    *type = t2;
    return r2;
  }

  /* Next is Integer */
  if (r1 == TYPE_INTEGER)
  {
    *type = t1;
    return r1;
  }

  if (r2 == TYPE_INTEGER)
  {
    *type = t2;
    return r2;
  }

  /* Well, we failed to decide... Let it be AUTO */
  *type = t_auto;
  return TYPE_AUTO;
}

/*
 * Deduce type of expression
 */
int deduce_expr_type(tree* expr, tree* parent, char** type)
{
  int ret = TYPE_AUTO;
  char *t1, *t2;
  int r1, r2;

  assert (expr != NULL);

  switch (expr->type)
  {
    case '+':
    case '-':
    case '*':
    case '/':
      r1 = deduce_expr_type(expr->left, parent, &t1);
      r2 = deduce_expr_type(expr->right, parent, &t2);
      /* Find most powerful type */
      ret = mix_types(r1, t1, r2, t2, type);
      break;

    case '%':
    case '|':
    case '^':
    case '&':
    case NODE_OP_LOR:
    case NODE_OP_LAND:
    case '!':
    case NODE_OP_NOT:
    case '>':
    case '<':
    case NODE_OP_EQ:
    case NODE_OP_NE:
    case NODE_OP_LE:
    case NODE_OP_GE:
    case NODE_CINT:
      ret = TYPE_INTEGER;
      *type = t_integer;
      break;

    case NODE_CFLOAT:
      ret = TYPE_REAL;
      *type = t_real;
      break;

    case NODE_CSTRING:
      ret = TYPE_STRING;
      *type = t_string;
      break;

    case NODE_IDENTIFIER:
      /* TODO: search for type in parent! */
      break;

    case NODE_ARRAY_USE:
    case NODE_FIELD_USE:
    case NODE_METH_INVOKE:
    case NODE_FUNC_CALL:
    default:
      /* Too much stuff to do here, not worth it */
      break;
  }

  return ret;
}

/*
 * Deduce type of statement
 * It's type of return statements or NULL
 */
int deduce_type_for_stmt(tree* list, tree* parent, char** type, int *retn_found)
{
  int ret = TYPE_AUTO;

  if (list != NULL)
  {
    switch (list->type)
    {
      case NODE_WHILE_STMT:
      case NODE_UNTIL_STMT:
        ret = deduce_type_for_stmt(list->right, parent, type, retn_found);
        break;
  
      case NODE_FOR_STMT:
        ret = deduce_type_for_stmt((tree*)list->param, parent, type, retn_found);
        break;
  
      case NODE_IF_STMT:
        ret = deduce_type_for_stmt(list->right, parent, type, retn_found);
        if (ret == TYPE_AUTO) /* Failed THEN - try ELSE */
          ret = deduce_type_for_stmt((tree*)list->param, parent, type, retn_found);
        break;
  
      case NODE_RETURN_STMT:
        if (list->value == NULL)
        {
          *type = t_void;
          ret = TYPE_VOID;
        } else {
          ret = deduce_expr_type(list->value, parent, type);
        }
        *retn_found = 1;
        break;
   
      case NODE_STMT_LIST:
        ret = deduce_type_for_stmt_list(list, parent, type, retn_found);
        break;
  
      default:
        /* Skip */
        break;
    }
  }

  return ret;
}

/*
 * Deduce type for list of statements
 * Just first RETURN will decide
 */
int deduce_type_for_stmt_list(tree* list, tree* parent, char** type, int* retn_found)
{
  int ret = TYPE_AUTO;

  while ((list != NULL) && (ret == TYPE_AUTO))
  {
    assert (list->type == NODE_STMT_LIST);

    tree *value = list->value;

    assert(value != NULL);

    ret = deduce_type_for_stmt(value, parent, type, retn_found);

    list = list->next;
  }

  return ret;
}

