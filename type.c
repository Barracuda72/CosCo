#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "tree.h"
#include "type.h"

char *t_integer = "int";
char *t_real = "double";
char *t_string = "std::string";
char *t_void = "void";
char *t_auto = "auto";

/*
 * VERY UGLY HACK
 */
static char* cur_func = NULL;
static char* cur_class = NULL;

/*
 * Deduce type for function
 * It's type of return statements or void, if there aren't any
 */
int deduce_func_type(tree* func, tree* parent, char **type)
{
  int ret = TYPE_AUTO;
  int retn_found = 0;

  assert (func->type == NODE_FUNC_DEF);

  /* UGLY HACK */
  tree *name = func->value;
  cur_func = name->left->value;
  if (name->right != NULL)
    cur_class = name->right->value;
  else
    cur_class = NULL;

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
 * Find identifier declaration
 */
tree *find_identifier(tree *ident, tree *scope)
{
  tree *res = NULL;

  if (scope != NULL)
  {
    switch (scope->type)
    {
      case NODE_STMT_LIST:
        while ((scope != NULL) && (res == NULL))
        {
          res = find_identifier(ident, scope->value);
          scope = scope->next;
        }
        break;
  
      case NODE_WHILE_STMT:
      case NODE_UNTIL_STMT:
        res = find_identifier(ident, scope->right);
        break;
  
      case NODE_FOR_STMT:
        res = find_identifier(ident, (tree*)scope->param);
        break;
  
      case NODE_IF_STMT:
        res = find_identifier(ident, scope->right);
        if (res == NULL) /* Failed THEN - try ELSE */
          res = find_identifier(ident, (tree*)scope->param);
        break;
  
      case NODE_VAR_DECL:
      case NODE_CONST_DECL:
        //fprintf(stderr, "Compare %s = %s\n", ident->value, scope->value->value);
        if (!strcmp(ident->value, scope->value->value))
          res = scope;
        break;
  
      default:
        /* Skip */
        break;
    }
  }

  return res;
}

/*
 * Deduce type of identifier
 * I know, I know, it's better to build type hash table and then use it...
 * But who cares?
 */
int deduce_identifier(tree* ident, tree *root, char** type)
{
  /* HACK for 'this' pointer */
  if (!strcasecmp(ident->value, "this"))
  {
    *type = cur_class;
    return TYPE_CUSTOM;
  }

  int ret;

  /* First, search for class and function scopes */
  tree *func_st = NULL;
  tree *class_st = NULL;
  tree *i = root;

  /* Search for class */
  if (cur_class != NULL)
  {
    while ((i != NULL) && (class_st == NULL))
    {
      assert (i->type == NODE_STMT_LIST);

      tree *value = i->value;
      assert (value != NULL);

      if (value->type == NODE_CLASS_DEF)
      {
        tree *name = value->value;
        assert (name != NULL);
        assert (name->value != NULL);
        if (!strcmp(name->value->value, cur_class))
        {
          class_st = value->right; 
        }
      }

      i = i->next;
    }
  }

  /* If class isn't found or not exists, search function in global scope */
  if (class_st == NULL)
    i = root;
  else
    i = class_st;

  while ((i != NULL) && (func_st == NULL))
  {
    assert (i->type == NODE_STMT_LIST);

    tree *value = i->value;
    assert (value != NULL);

    if (value->type == NODE_FUNC_DEF)
    {
      tree *name = value->value;
      assert (name != NULL);
      assert (name->value != NULL);
      if (!strcmp(name->value->value, cur_func))
      {
        func_st = value->right; 
      }
    }

    i = i->next;
  }

  //fprintf(stderr, "Search for %s in %s:%s", ident->value, cur_class, cur_func);

  /* Now search for declaration */
  tree *decl = NULL;

  if (func_st != NULL)
    decl = find_identifier(ident, func_st);

  if ((decl == NULL) && (class_st != NULL))
    decl = find_identifier(ident, class_st);

  if (decl == NULL)
    decl = find_identifier(ident, root);

  if (decl == NULL) /* Not found */
    ret = TYPE_AUTO;
  else {
    switch (decl->type)
    {
      case NODE_CONST_DECL:
        /* Determine type of initializing expression */
        ret = deduce_expr_type(decl->right, NULL, type);
        break;
      
      case NODE_VAR_DECL:
        /* A bit of STRCMP */
        *type = decl->right->value;

        if (!strcmp(*type, t_integer))
          ret = TYPE_INTEGER;

        else if (!strcmp(*type, t_real))
          ret = TYPE_REAL;

        else if (!strcmp(*type, t_string))
          ret = TYPE_STRING;

        else
          ret = TYPE_CUSTOM;
  
        break;
  
      default:
        /* Should not happen */
        break;
    }
  }

  //fprintf(stderr, "... decided to be %d (%s)\n", ret, *type);

  return ret;
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
      ret = deduce_identifier(expr, parent, type);
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

