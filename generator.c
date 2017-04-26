#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <assert.h>

#include "tree.h"
#include "generator.h"

/*
 * Marker used for field or method access
 */
static const char *invoke_marker = "->";

/*
 * Mark end of statement
 */
void generate_statement_end(FILE *output)
{
  fprintf(output, ";\n");
}

void generate_var_decl_stmt(FILE *output, tree *node, int level)
{
  make_indent(output, level);
  generate_var_decl(output, node, level);
  generate_statement_end(output);
}

/*
 * Generate one statement
 */
void generate_statement(FILE *output, tree *node, int level)
{
  assert(node != NULL);

  switch (node->type)
  {
    case NODE_VAR_DECL:
      generate_var_decl_stmt(output, node, level);
      break;

    case NODE_FUNC_DEF:
      generate_function_def(output, node, level);
      break;

    case NODE_CLASS_DEF:
      generate_class_def(output, node, level);
      break;

    case NODE_UNTIL_STMT:
      generate_until(output, node, level);
      break;

    case NODE_WHILE_STMT:
      generate_while(output, node, level);
      break;

    case NODE_FOR_STMT:
      generate_for(output, node, level);
      break;

    case NODE_IF_STMT:
      generate_if(output, node, level);
      break;

    case NODE_STMT_LIST:
      generate_statement_list(output, node, level+1);
      break;

    case NODE_ASSIGN:
      generate_assign(output, node, level);
      break;

    case NODE_RETURN_STMT:
      generate_return(output, node, level);
      break;

    case NODE_BREAK_STMT:
      generate_break(output, node, level);
      break;

    case NODE_FUNC_CALL:
      make_indent(output, level);
      generate_function_call(output, node, level);
      generate_statement_end(output);
      break;

    case NODE_METH_INVOKE:
      make_indent(output, level);
      generate_meth_invoke(output, node, level);
      generate_statement_end(output);
      break;

    case NODE_CONST_DECL:
      generate_const_decl(output, node, level);
      break;

    default:
      make_indent(output, level);
      fprintf(output, "Node %d\n", node->type);
      break;
  }
}

void make_indent(FILE *output, int level)
{
  for (int i = 0; i < level<<1; i++)
    fputc(' ', output);
}

/*
 * Generate function call or method invocation
 */
void generate_call(FILE *output, tree *node, int level)
{
  assert(node->type == NODE_FUNC_CALL);

  make_indent(output, level);
  fprintf(output, "FUNC CALL!");
  generate_statement_end(output);
}

/*
 * Generate BREAK statement
 */
void generate_break(FILE *output, tree *node, int level)
{
  assert(node->type == NODE_BREAK_STMT);

  make_indent(output, level);
  fprintf(output, "break");
  generate_statement_end(output);
}

/*
 * Generate return statement
 */
void generate_return(FILE *output, tree *node, int level)
{
  assert(node -> type = NODE_RETURN_STMT);

  make_indent(output, level);
  fprintf(output, "return ");
  if (node->left) /* If it's not void */
    generate_expression(output, node->left, level);
  generate_statement_end(output);
}

/*
 * Generate assignment operator
 */
void generate_assign(FILE *output, tree *node, int level)
{
  assert(node->type == NODE_ASSIGN);

  make_indent(output, level);
  generate_var_use(output, node->left, level);
  fprintf(output, " = ");
  generate_expression(output, node->right, level);
  generate_statement_end(output);
}

/*
 * Print identifier
 */
void generate_identifier(FILE *output, tree *node, int level)
{
  assert (node->type == NODE_IDENTIFIER);

  fprintf(output, node->left);
}

/*
 * Unfold and generate variable use
 */
void generate_var_use(FILE *output, tree *node, int level)
{
  assert(node != NULL);

  tree *t = NULL;

  switch (node->type)
  {
    case NODE_IDENTIFIER:
      generate_identifier(output, node, level);
      break;

    case NODE_ARRAY_USE:
      generate_expression(output, node->left, level);
      fprintf(output, "[");
      t = node->right;
      while (t->next != NULL)
      {
        generate_expression(output, t->value, level);
        fprintf(output, ", ");
        t = t->next;
      }
      /* Last piece */
      generate_expression(output, t->value, level);
      fprintf(output, "]");
      break;

    case NODE_FIELD_USE:
      generate_expression(output, node->left, level);
      fprintf(output, invoke_marker);
      generate_var_use(output, node->right, level);
      break;

    case NODE_METH_INVOKE:
      generate_meth_invoke(output, node, level);
      break;

    case NODE_FUNC_CALL:
      generate_function_call(output, node, level);
      break;

    default:
      fprintf(output, "$VARUSE TODO: %d$", node->type);
      break;
  }
}

/*
 * Generate constant use
 */
void generate_const_use(FILE *output, tree *node, int level)
{
  assert(
    node->type == NODE_CSTRING ||
    node->type == NODE_CINT ||
    node->type == NODE_CFLOAT
  );

  long tmp;

  switch (node->type)
  {
    case NODE_CSTRING:
      /* TODO: should be this! */
      //fprintf(output, "\"%s\"", (char*)(node->left));
      fprintf(output, "%s", (char*)(node->left));
      break;

    case NODE_CINT:
      fprintf(output, "%d", (long)(node->left));
      break;

    case NODE_CFLOAT:
      /* Very hackish! */
      tmp = (long)(node->left);
      fprintf(output, "%f", *(double*)&tmp);
      break;
  }
}

/*
 * Generate FOR loop
 */
void generate_for(FILE *output, tree *node, int level)
{
  assert(node->type == NODE_FOR_STMT);
  //assert(node->left->type == NODE_ASSIGN);

  char *op = NULL;
  char *dir = NULL;

  if (node->id == FOR_DIR_FWD)
  {
    op = " <= ";
    dir = "++";
  } else {
    op = " >= ";
    dir = "--";
  }

  make_indent(output, level);
  fprintf(output, "for (");

  /* Initalization */
  generate_statement(output, node->left, 0);
  fprintf(output, " ");

  /* Resume condition */
  tree *var = node->left->left;
  tree *cond = node->right;
  generate_var_use(output, var, 0);
  fprintf(output, op);
  generate_expression(output, cond, 0);
  fprintf(output, "; ");

  /* Step */
  generate_var_use(output, var, 0);
  fprintf(output, dir);

  fprintf(output, ")\n");

  /* Statements */
  make_indent(output, level);
  fprintf(output, "{\n");
  tree *stmt = (tree*)node->param;
  if (stmt != NULL)
  {
    generate_statement(output, stmt, level+1);
  }
  make_indent(output, level);
  fprintf(output, "}\n");
}

/*
 * Generate IF conditional statement
 */
void generate_if(FILE *output, tree *node, int level)
{
  assert(node->type == NODE_IF_STMT);

  make_indent(output, level);
  fprintf(output, "if (");
  generate_expression(output, node->left, level);
  fprintf(output, ")\n");

  /* THEN Statements */
  make_indent(output, level);
  fprintf(output, "{\n");
  if (node->right != NULL)
  {
    generate_statement_list(output, node->right, level+1);
  }
  make_indent(output, level);
  fprintf(output, "}\n");

  /* ELSE Statements */
  tree *telse = (tree*)node->param;
  if (telse != NULL)
  {
    make_indent(output, level);
    fprintf(output, "else {\n");
    generate_statement(output, telse, level+1);
    make_indent(output, level);
    fprintf(output, "}\n");
  }
}

/*
 * Protect some types of expression
 */
void generate_expression_protect(FILE *output, tree *node, int level, int c)
{
  assert (node != NULL);

  switch (node->type)
  {
    case NODE_CINT:
    case NODE_CFLOAT:
    case NODE_CSTRING:
    case NODE_ARRAY_USE:
    case NODE_FIELD_USE:
    case NODE_IDENTIFIER:
    case NODE_FUNC_CALL:
    case NODE_METH_INVOKE:
      /* Do not protect */
      break;

    default:
      fprintf(output, "%c", c);
      break;
  }
}

/*
 * Generate expression with braces around if required
 */
void generate_expression(FILE *output, tree *node, int level)
{
  generate_expression_protect(output, node, level, '(');
  generate_expression_unprotected(output, node, level);
  generate_expression_protect(output, node, level, ')');
}

/*
 * Generate expression (without braces protection)
 */
void generate_expression_unprotected(FILE *output, tree *node, int level)
{
  assert(node != NULL);

  switch (node->type)
  {
    /* Simple operations */
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '|':
    case '^':
    case '&':
    case '>':
    case '<':
    case NODE_OP_EQ:
    case NODE_OP_NE:
    case NODE_OP_LE:
    case NODE_OP_GE:
    case NODE_OP_LOR:
    case NODE_OP_LAND:
      generate_expression(output, node->left, level);
      if (node->type < NODE_OP_START)
        fprintf(output, " %c ", node->type);
      else
        switch (node->type)
        {
          case NODE_OP_EQ:
            fprintf(output, " == ");
            break;
          
          case NODE_OP_NE:
            fprintf(output, " != ");
            break;
          
          case NODE_OP_LE:
            fprintf(output, " <= ");
            break;
          
          case NODE_OP_GE:
            fprintf(output, " >= ");
            break;
          
          case NODE_OP_LOR:
            fprintf(output, " || ");
            break;
          
          case NODE_OP_LAND:
            fprintf(output, " && ");
            break;
          
          default:
            fprintf(output, " $UNKOP$ ");
            break;
        }
        
      generate_expression(output, node->right, level);
      break;

    case '!':
    case NODE_OP_NOT:
      fprintf(output, "!");
      generate_expression(output, node->value, level);
      break;

    case NODE_CINT:
    case NODE_CFLOAT:
    case NODE_CSTRING:
      generate_const_use(output, node, level);
      break;

    case NODE_IDENTIFIER:
      generate_identifier(output, node, level);
      break;

    case NODE_ARRAY_USE:
    case NODE_FIELD_USE:
      generate_var_use(output, node, level);
      break;

    case NODE_METH_INVOKE:
      generate_meth_invoke(output, node, level);
      break;

    case NODE_FUNC_CALL:
      generate_function_call(output, node, level);
      break;

    default:
      fprintf (output, "$EXPRESSION TODO: %d$", node->type);
      break;
  }
}

/*
 * Generate WHILE loop
 */
void generate_while(FILE *output, tree *node, int level)
{
  assert(node->type == NODE_WHILE_STMT);

  make_indent(output, level);
  fprintf(output, "while (");
  generate_expression(output, node->left, level);
  fprintf(output, ")\n");

  /* Statements */
  make_indent(output, level);
  fprintf(output, "{\n");
  if (node->right != NULL)
  {
    generate_statement_list(output, node->right, level+1);
  }
  make_indent(output, level);
  fprintf(output, "}\n");
}

/*
 * Generate UNTIL loop
 */
void generate_until(FILE *output, tree *node, int level)
{
  assert(node->type == NODE_UNTIL_STMT);

  /* Statements */
  make_indent(output, level);
  fprintf(output, "do {\n");
  if (node->right != NULL)
  {
    generate_statement_list(output, node->right, level+1);
  }
  make_indent(output, level);
  fprintf(output, "} while (!("); /* Invert condition */
  generate_expression(output, node->left, level);
  fprintf(output, "));\n");
}

/*
 * Generate class header (just name)
 */
void generate_class_head(FILE *output, tree *node, int level)
{
  assert(node->type == NODE_CLASS_DEF);

  fprintf(output, "struct ");

  tree *name = node->value;

  generate_identifier(output, name->left, level);
  generate_statement_end(output);
}


/*
 * Generate class declaration
 */
void generate_class_decl(FILE *output, tree *node, int level)
{
  assert(node->type == NODE_CLASS_DEF);

  fprintf(output, "struct ");

  tree *name = node->value;

  if (name->right != NULL)
  {
    /* Has base class */
    generate_identifier(output, name->left, level);
    fprintf(output, " : ");
    generate_identifier(output, name->right, level);
  } else {
    generate_identifier(output, name->left, level);
  }

  fprintf(output, "\n{\n");
  tree *stmts = node->right;
  while (stmts != NULL)
  {
    assert(stmts->type == NODE_STMT_LIST);
    tree *node = stmts->value;
    assert(node != NULL);

    /* Generate variable declaration and method prototypes */
    switch(node->type)
    {
      case NODE_VAR_DECL:
        generate_var_decl_stmt(output, node, level+1);
        break;

      case NODE_FUNC_DEF:
        generate_function_head(output, node, level+1);
        break;

      default:
        /* Skip everything else (there shouldn't be but that if...) */
        break;
    }

    stmts = stmts->next;
  }
  fprintf(output, "};\n\n");
}

/*
 * Generate class implementation
 */
void generate_class_impl(FILE *output, tree *node, int level)
{
  assert(node->type == NODE_CLASS_DEF);

  tree *stmts = node->right;

  while (stmts != NULL)
  {
    assert (stmts -> type == NODE_STMT_LIST);

    tree *t = stmts->value;

    assert (t != NULL);

    if (t->type == NODE_FUNC_DEF)
      generate_function_def(output, t, level);

    stmts = stmts->next;
  }
}

/*
 * Generate class definition
 */
void generate_class_def(FILE *output, tree *node, int level)
{
  assert(node->type == NODE_CLASS_DEF);

  //fprintf(output, "class "); /* Better be struct */
  fprintf(output, "struct ");

  tree *name = node->value;

  if (name->right != NULL)
  {
    /* Has base class */
    generate_identifier(output, name->left, level);
    fprintf(output, " : ");
    generate_identifier(output, name->right, level);
  } else {
    generate_identifier(output, name->left, level);
  }

  fprintf(output, "\n{\n");
  if (node->right)
  {
    /* Statements */
    generate_statement_list(output, node->right, level+1);
  }
  fprintf(output, "}\n\n");
}

/*
 * Generate variable declaration (without creation)
 */
void generate_var_decl(FILE *output, tree *node, int level)
{
  assert(node->type == NODE_VAR_DECL);
  
  generate_identifier(output, node->right, level);
  fprintf(output, " ");
  generate_identifier(output, node->left, level);
}

/*
 * Generate constant declaration
 */
void generate_const_decl(FILE *output, tree *node, int level)
{
  assert (node->type == NODE_CONST_DECL);

  make_indent(output, level);
  fprintf(output, "#define ");
  generate_identifier(output, node->left, level);
  fprintf(output, " ");
  generate_expression(output, node->right, level);
  fprintf(output, "\n");
}

/*
 * Parse list of statements
 */
void generate_statement_list(FILE *output, tree *node, int level)
{
  assert(node->type == NODE_STMT_LIST);

  while (node != NULL)
  {
    generate_statement(output, node->value, level);
    node = node -> next;
  }
}

/*
 * Generate only method call
 */
void generate_meth_invoke(FILE *output, tree *node, int level)
{
  assert(node->type == NODE_METH_INVOKE);

  generate_expression(output, node->left, level);
  fprintf(output, invoke_marker);
  generate_function_call(output, node->right, level);
}
/*
 * Generate function or method call
 */
void generate_function_call(FILE *output, tree *node, int level)
{
  assert(node->type == NODE_FUNC_CALL);

  generate_var_use(output, node->left, level);

  fprintf(output, "(");
  tree *params = node->right;
  if (params != NULL)
  {
    while (params->next != NULL)
    {
      generate_expression(output, params->value, level);
      fprintf(output, ", ");
      params = params->next;
    }
    /* Last piece */
    generate_expression(output, params->value, level);
  }
  fprintf(output, ")");
}

/*
 * Generate function header (prototype)
 */
void generate_function_head(FILE *output, tree *node, int level)
{
  assert(node->type == NODE_FUNC_DEF);

  make_indent(output, level);
  /* Put 'auto' keyword instead of type and let compiler deduce it */
  if (node->id != FTYPE_CONSTRUCTOR)
  {
    fprintf(output, "auto ");
  }

  tree *name = node->left;
  assert(name->type == NODE_FUNC_NAME);

  generate_identifier(output, name->left, level);
  
  /* Parameters */
  fprintf(output, "(");
  if (node->param)
  {
    tree *params = (tree*)node->param;
    while (params->next != NULL)
    {
      generate_var_decl(output, params->value, 0);
      fprintf(output, ", ");
      params = params->next;
    }
    /* Add one missing */
    generate_var_decl(output, params->value, 0);
  }
  fprintf(output, ");\n");
}

/*
 * Generate function code
 */
void generate_function_def(FILE *output, tree *node, int level)
{
  assert(node->type == NODE_FUNC_DEF);

  make_indent(output, level);
  /* Put 'auto' keyword instead of type and let compiler deduce it */
  if (node->id != FTYPE_CONSTRUCTOR)
  {
    fprintf(output, "auto ");
  }

  tree *name = node->left;
  assert(name->type == NODE_FUNC_NAME);
  if (name->right)
  {
    /* It's a method */
    generate_identifier(output, name->right, level);
    fprintf(output, "::");
  }

  generate_identifier(output, name->left, level);
  
  /* Parameters */
  fprintf(output, "(");
  if (node->param)
  {
    tree *params = (tree*)node->param;
    while (params->next != NULL)
    {
      generate_var_decl(output, params->value, 0);
      fprintf(output, ", ");
      params = params->next;
    }
    /* Add one missing */
    generate_var_decl(output, params->value, 0);
  }
  fprintf(output, ")\n");

  /* Body */
  make_indent(output, level);
  fprintf(output, "{\n");
  if (node->right)
    generate_statement_list(output, node->right, level+1);
  make_indent(output, level);
  fprintf(output, "}\n\n");
}

/*
 * Implement foreach loop with condition and functor
 */
void generator_foreach_cond(FILE *output, tree *root, int node_type, void (*generator)(FILE*, tree*, int))
{
  while (root != NULL)
  {
    assert (root->type == NODE_STMT_LIST);

    tree *node = root->value;

    assert (node != NULL);

    if (node->type == node_type)
      generator(output, node, 0);

    root = root->next;
  }
}

/*
 * Generate the whole program
 */
void generate_program(FILE *output, tree *root)
{
  /* Step 0: output runtime inclusion */
  fprintf(output, "#include \"Runtime.h\"\n");

  /* Step 1: generate defines (constants) */
  fprintf(output, "\n/*\n * Constants\n */\n\n");
  generator_foreach_cond(output, root, NODE_CONST_DECL, generate_const_decl);

  /* Step 2a: generate class declarations (headers) */
  fprintf(output, "\n/*\n * Class declarations (headers)\n */\n\n");
  generator_foreach_cond(output, root, NODE_CLASS_DEF, generate_class_head);

  /* Step 2b: generate class declarations (bodies) */
  fprintf(output, "\n/*\n * Class declarations (bodies)\n */\n\n");
  generator_foreach_cond(output, root, NODE_CLASS_DEF, generate_class_decl);

  /* Step 3: generate all variables */
  fprintf(output, "\n/*\n * Variables\n */\n\n");
  generator_foreach_cond(output, root, NODE_VAR_DECL, generate_var_decl_stmt);

  /* Step 4: generate standalone functions: headers first, then code */
  fprintf(output, "\n/*\n * Standalone functions (headers)\n */\n\n");
  generator_foreach_cond(output, root, NODE_FUNC_DEF, generate_function_head);
  fprintf(output, "\n/*\n * Standalone functions (bodies)\n */\n\n");
  generator_foreach_cond(output, root, NODE_FUNC_DEF, generate_function_def);

  /* Step 5: generate class methods */
  fprintf(output, "\n/*\n * Class implementations\n */\n\n");
  generator_foreach_cond(output, root, NODE_CLASS_DEF, generate_class_impl);
}

