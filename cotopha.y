%{
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tree.h"
#include "backend.h"

extern char *yytext;
extern int yylineno;
extern int yycharpos;
extern int yyleng;
extern FILE *yyin;
#ifdef DEBUG
extern int yydebug;
#endif

#define YYSTYPE unsigned long

void eputs(char *s)
{
  fprintf(stderr, "%s\n", s);
}

void yyerror(const char *s)
{
  int c = yycharpos - yyleng;
  int i,k;

  char *t = malloc(2048);
  sprintf(t, "^ Error: \"%s\" at %d:%d, got '%s'",
    s, yylineno, c, yytext);
#if 0
  while ((k = getc(yyin)) != EOF)
  {
    putchar(k);
    if ((k == '\n') && (t != 0))
    {
      for (i = 1; i < c; i++)
        putchar('*');
      puts(t);

      free(t);
      t = 0;
    }
  }
#else
  puts(t);
  free(t);
#endif
}

int yywrap()
{
  return 1;
}

tree *root = NULL;

int main(int argc, char *argv[])
{
#ifdef DEBUG
  yydebug = 1;
#endif
  yyparse();

  if (root == NULL)
    eputs("There were some errors; compilation aborted");
  else
    backend_process(root);
}

%}

%token 
  TOK_DECLARETYPE TOK_EXTRNDEF
  TOK_INCLUDE TOK_CONSTANT
  TOK_BEGIN TOK_END
  TOK_STRUCTURE TOK_ENDSTRUCT 
  TOK_FUNCTION TOK_ENDFUNC TOK_RETURN 
  TOK_IF TOK_ELSE TOK_ENDIF TOK_ELSEIF 
  TOK_REPEAT TOK_UNTIL 
  TOK_FOR TOK_TO TOK_DOWNTO TOK_NEXT 
  TOK_WHILE TOK_ENDWHILE TOK_BREAK
  TOK_ASSIGN TOK_ADD_ASS TOK_SUB_ASS TOK_MUL_ASS TOK_DIV_ASS 
  TOK_OR_ASS TOK_AND_ASS
  TOK_LEQ TOK_GEQ TOK_EQ TOK_NEQ 
  TOK_AND TOK_OR TOK_NOT
  TOK_DOUBLEDOT TOK_QUADDOT TOK_ID_OPERATE
  TOK_UNSIGNED_INTEGER TOK_FLOAT TOK_HEX_INTEGER TOK_CSTRING TOK_IDENTIFIER
  TOK_M_IF TOK_M_ELSE TOK_M_ENDIF TOK_M_ISDEFINED 

%%

/*
 * Program consists of blocks
 */

program: 
  block_list { root = $1; }
  ;

/*
 * List of blocks
 */
block_list: 
  { $$ = NULL; } | 
  block block_list
  {
    $$ = tree_link_lists($1, $2);
  }
  ;

/*
 * Block can be:
 * a) Function definition
 * b) Structure definition
 * c) Macro operation
 * d) Include operation
 * e) Variable declaration
 * f) Constant definition
 * g) Type declaration
 * h) Some procedural actions
 * i) Extern declaration
 */

block:
  function_def |
  structure_def |
  macro_op |
  include_op |
  var_declaration |
  constant_definition |
  type_declaration |
  proc_actions |
  extern_declaration 
  ;

/*
 * Extern declaration
 */
extern_declaration:
  TOK_EXTRNDEF identifier
  {
    tree *node = tree_create($2, NULL, NODE_EXTERN_DECL); 
    $$ = tree_create(node, NULL, NODE_STMT_LIST);
  }
  ;

/*
 * Procedural actions
 */
proc_actions:
  operator_list 
  ;

/*
 * Type declaration
 */
type_declaration:
  TOK_DECLARETYPE identifier
  {
    tree *node = tree_create($2, NULL, NODE_CLASS_DECL); 
    $$ = tree_create(node, NULL, NODE_STMT_LIST);
  }
  ;

/*
 * Include operation
 */
include_op: 
  TOK_INCLUDE TOK_CSTRING
  {
    // TODO: DO NOT IGNORE?
    $$ = NULL;
  }
  ;

/*
 * Macro operation
 */
macro_op: 
  TOK_M_IF macro_expr block_list TOK_M_ENDIF { /* TODO: Ignore? */ $$ = NULL; } |
  TOK_M_IF macro_expr block_list TOK_M_ELSE block_list TOK_M_ENDIF { /* TODO: Ignore? */ $$ = NULL; }
  ;

/*
 * Macro conditional expression
 * TODO: Very basic for now!
 */
macro_expr: 
  '(' macro_cond ')' { /* TODO: Ignore? */ $$ = NULL; } | 
  macro_cond { /* TODO: Ignore? */ $$ = NULL; }
  ;

/*
 * Macro condition
 */
macro_cond:
  macro_cond_left TOK_EQ TOK_UNSIGNED_INTEGER
  { /* TODO: Ignore? */ $$ = NULL; }
  ;

/*
 * Left side of macro condition
 */
macro_cond_left:
  macro_isdefined { /* TODO */ $$ = NULL; } | 
  identifier { /* TODO */ $$ = NULL; }
  ;

/*
 * IsDefined construct
 */
macro_isdefined:
  TOK_M_ISDEFINED '(' TOK_CSTRING ')'
  { /* TODO */ $$ = NULL; }
  ;

/*
 * Function definition
 */

function_def: 
  TOK_FUNCTION function_name '(' function_parameters ')'
    function_statements
  TOK_ENDFUNC
  {
    tree *node = tree_create_ex($2, $6, NODE_FUNC_DEF, FTYPE_GENERIC, $4);
    $$ = tree_create(node, NULL, NODE_STMT_LIST);
  }
  ;

/*
 * Function parameters
 */
function_parameters:
  { $$ = NULL; } | 
  parameter_list
  ;

/*
 * List of function parameters
 */
parameter_list:
  parameter | 
  parameter_list ',' parameter 
  { 
    $$ =  tree_link_lists($1, $3); 
  }
  ;

/*
 * One of function parameters
 */
parameter:
  identifier identifier
  {
    tree *node = tree_create($2, $1, NODE_VAR_DECL);
    $$ = tree_create(node, NULL, NODE_STMT_LIST);
  }
  ;

/*
 * Statements inside function
 */
function_statements:
  operator_list
  ;

operator:
  simple_operator | 
  complex_operator
  ;

simple_operator:
  var_declaration | 
  assign_operator | 
  func_call | 
  empty_operator
  ;

pure_assign_operator:
  variable TOK_ASSIGN expression
  {
    tree *node = tree_create($1, $3, NODE_ASSIGN);
    //$$ = tree_create(node, NULL, NODE_STMT_LIST);
    $$ = node;
  }
  ;

assign_operator:
  variable assignment_operation expression
  {
    /*
     * Break things up
     */
    tree *op = (tree*)$3;
    
    if ($2 != '=')
    {
      op = tree_create($1, $3, $2);
    }

    tree *node = tree_create($1, op, NODE_ASSIGN);

    //$$ = tree_create(node, NULL, NODE_STMT_LIST);
    $$ = node;
  }
  ;

assignment_operation:
  TOK_ASSIGN  { $$ = '='; } |
  TOK_AND_ASS { $$ = '&'; } |
  TOK_OR_ASS  { $$ = '|'; } |
  TOK_ADD_ASS { $$ = '+'; } |
  TOK_SUB_ASS { $$ = '-'; } |
  TOK_MUL_ASS { $$ = '*'; } |
  TOK_DIV_ASS { $$ = '/'; }
  ;

variable:
  part_variable | full_variable
  ;

full_variable:
  identifier
  ;

part_variable:
  indexed_variable | field_variable
  ;

indexed_variable:
  variable '[' expression_comma_list ']'
  {
    $$ = tree_create($1, $3, NODE_ARRAY_USE);
  }
  ;

expression_comma_list:
  expression 
  {
    $$ = tree_create($1, NULL, NODE_STMT_LIST);
  }
  |
  expression_comma_list ',' expression
  {
    tree *node = tree_create($3, NULL, NODE_STMT_LIST);
    $$ = tree_link_lists($1, node);
  }
  ;

field_variable:
  variable '.' variable
  {
    $$ = tree_create($1, $3, NODE_FIELD_USE);
  }
  ;

expression:
  simple_expression | 
  simple_expression rela_operation simple_expression
  {
    $$ = tree_create($1, $3, $2);
  }
  ;

rela_operation:
  TOK_EQ { $$ = NODE_OP_EQ; } | 
  TOK_NEQ { $$ = NODE_OP_NE; } | 
  '<' { $$ = '<'; } | 
  '>' { $$ = '>'; } | 
  TOK_LEQ { $$ = NODE_OP_LE; } | 
  TOK_GEQ { $$ = NODE_OP_GE; }
  ;

unsigned:
  TOK_UNSIGNED_INTEGER 
  {
    $$ = tree_create(strtol($1, NULL, 10), NULL, NODE_CINT);
  } | 
  TOK_FLOAT 
  {
    /* Shooting in the foot! */
    double p = strtod($1, NULL);
    $$ = tree_create((tree*)(*(long*)&p), NULL, NODE_CFLOAT);
  } | 
  TOK_HEX_INTEGER /* SHOULD NOT BELONG HERE!!! */
  {
    $$ = tree_create(strtol($1, NULL, 16), NULL, NODE_CINT);
  }
  ;

optional_sign:
  { $$ = '+'; } | 
  sign
  ;

sign:
  '+' { $$ = '+'; } | 
  '-' { $$ = '-'; }
  ;

simple_expression:
  optional_sign terms
  {
    tree *node = (tree*)$2;

    /* Pretty hackish */
    if ($1 == '-')
    {
      tree *nul = tree_create(0, NULL, NODE_CINT);
      node = tree_create(nul, $2, '-');
    }

    $$ = node;
  }
  ;

terms:
  term | 
  terms add_operation term
  {
    $$ = tree_create($1, $3, $2);
  }
  ;

add_operation:
  '+' { $$ = '+'; } | 
  '-' { $$ = '-'; } | 
  '|' { $$ = '|'; } |
  '^' { $$ = '^'; } |
  TOK_OR { $$ = NODE_OP_LOR; }
  ;

term:
  factor | 
  term mult_operation factor
  {
    $$ = tree_create($1, $3, $2);
  }
  ;

mult_operation:
  '*' { $$ = '*'; } | 
  '/' { $$ = '/'; } | 
  '%' { $$ = '%'; } | 
  '&' { $$ = '&'; } |
  TOK_AND { $$ = NODE_OP_LAND; }
  ;

factor:
  object_provider |
  unsigned_constant | 
  TOK_NOT factor { $$ = tree_create($2, NULL, NODE_OP_NOT); } |
  '!' factor { $$ = tree_create($2, NULL, NODE_OP_NOT); }
  ;

objectable:
  variable |
  func_call |
  '(' expression ')' { $$ = $2; }
  ;

object_provider:
  object_provider '.' func_call { $$ = tree_create($1, $3, NODE_METH_INVOKE); } |
  object_provider '.' variable { $$ = tree_create($1, $3, NODE_FIELD_USE); } |
  objectable
  ;

unsigned_constant:
  unsigned |
  TOK_CSTRING { $$ = tree_create($1, NULL, NODE_CSTRING); } /* identifier */
  ;

func_call:
  variable '(' call_params ')'
  {
    $$ = tree_create($1, $3, NODE_FUNC_CALL);
  }
  ;

call_params:
  {$$ = NULL; } | 
  call_params_list
  ;

call_params_list:
  call_param { $$ = tree_create($1, NULL, NODE_STMT_LIST); } | 
  call_params_list ',' call_param
  {
    tree *node = tree_create($3, NULL, NODE_STMT_LIST);
    $$ = tree_link_lists($1, node);
  }
  ;

call_param:
  expression 
  ;

empty_operator:
  { $$ = NULL; }
  ;

operator_list:
  operator 
  { 
    if ($1 != NULL) /* Empty operator - function or smthng has no operators */
      $$ = tree_create($1, NULL, NODE_STMT_LIST); 
    else
      $$ = NULL;
  } | 
  operator_list operator
  {
    /* Should not meet empty operator here */
    tree *node = tree_create($2, NULL, NODE_STMT_LIST);
    $$ = tree_link_lists($1, node);
  }
  ;

complex_operator: 
  if_operator | 
  loop_operator | 
  return_operator | 
  break_operator
  ;

break_operator:
  TOK_BREAK
  {
    $$ = tree_create(NULL, NULL, NODE_BREAK_STMT);
  }
  ;

if_operator:
  TOK_IF expression operator_list if_tail
  {
    /* Somethat hackish */
    $$ = tree_create_ex($2, $3, NODE_IF_STMT, -1, $4);
  }
  ;

if_tail:
  TOK_ENDIF { $$ = NULL; } |
  TOK_ELSE operator_list TOK_ENDIF { $$ = $2; } |
  TOK_ELSEIF expression operator_list if_tail
  {
    /*
     * Transform into else - if pair
     */
    $$ = tree_create_ex($2, $3, NODE_IF_STMT, -1, $4);
  }
  ;

loop_operator:
  while_operator | repeat_operator | for_operator
  ;

while_operator:
  TOK_WHILE expression operator_list TOK_ENDWHILE
  {
    $$ = tree_create($2, $3, NODE_WHILE_STMT);
  }
  ;

repeat_operator:
  TOK_REPEAT operator_list TOK_UNTIL expression
  {
    $$ = tree_create($4, $2, NODE_UNTIL_STMT);
  }
  ;

for_operator:
  TOK_FOR assign_operator for_direction expression operator_list TOK_NEXT
  {
    /* Very hackish */
    $$ = tree_create_ex($2, $4, NODE_FOR_STMT, $3, $5);
  }
  ;

for_direction:
  TOK_TO { $$ = FOR_DIR_FWD; } | 
  TOK_DOWNTO { $$ = FOR_DIR_BWD; }
  ;

return_operator:
  TOK_RETURN expression { $$ = tree_create($2, NULL, NODE_RETURN_STMT); }|
  TOK_RETURN { $$ = tree_create(NULL, NULL, NODE_RETURN_STMT); }
  ;

constant_definition:
  TOK_CONSTANT decl_list
  {
    /*
     * Copy only assignment nodes and purge all other
     */
    tree *h = (tree*)$2;
    tree *n = NULL;
    tree *t = NULL;

    while (h != NULL)
    {
      assert(h->value != NULL);
      assert(h->value->type == NODE_ASSIGN || h->value->type == NODE_VAR_DECL);

      t = h->next;

      if (h->value->type == NODE_ASSIGN)
      {
        /* Change type and add to new list */
        h->value->type = NODE_CONST_DECL;
        h->next = NULL;
        n = tree_link_lists(n, h);
      } else /* NODE_VAR_DECL */ {
        /* Purge */
        /* Left is still used */
        /* Right is NULL */
        free(h->value);
        free(h);
      }

      h = t;
    }
    $$ = n;
  }
  ;

var_declaration:
  identifier decl_list
  {
    /*
     * Set var type for all declarations
     */
    tree *h = (tree*)$2;
    while (h != NULL)
    {
      assert(h->value != NULL);
      if (h->value->type == NODE_VAR_DECL)
        h->value->next = $1;
      h = h->next;
    }
    $$ = $2;
  }
  ;

decl_list:
  single_declaration { $$ = $1; } | 
  single_declaration ',' decl_list { $$ = tree_link_lists($1, $3); }
  ;

single_declaration:
  simple_declaration 
  { 
    tree *node = tree_create($1, NULL, NODE_VAR_DECL);
    $$ = tree_create(node, NULL, NODE_STMT_LIST);
  } | 
  complex_declaration
  {
    /*
     * Split into two nodes : declaration and assignment
     */
    char *name = ((tree*)$1)->left;
    tree *node = tree_create(name, NULL, NODE_VAR_DECL);
    tree *stmt = tree_create($1, NULL, NODE_STMT_LIST);
    $$ = tree_create(node, stmt, NODE_STMT_LIST);
  }
  ;

simple_declaration:
  identifier
  ;

complex_declaration:
  identifier TOK_ASSIGN expression { $$ = tree_create($1, $3, NODE_ASSIGN); }
  ;

/*
 * Function name (can include class)
 */
function_name:
  identifier TOK_QUADDOT identifier { $$ = tree_create($3, $1, NODE_FUNC_NAME); } |
  identifier TOK_QUADDOT TOK_ID_OPERATE 
  { 
    /* TODO: HACK! replace! */
    tree *disp = tree_create(OP_DISPATCHER, NULL, NODE_IDENTIFIER);
    $$ = tree_create(disp, $1, NODE_FUNC_NAME); 
  } |
  identifier { $$ = tree_create($1, NULL, NODE_FUNC_NAME); }
  ;

/*
 * Structure definition
 */
structure_def:
  TOK_STRUCTURE structure_name
    structure_content
  TOK_ENDSTRUCT
  { 
    tree *node = tree_create($2, $3, NODE_CLASS_DEF); 
    $$ = tree_create(node, NULL, NODE_STMT_LIST);
  }
  ;

/*
 * Structure name (can include base class)
 */
structure_name:
  identifier ':' identifier { $$ = tree_create($1, $3, NODE_CLASS_NAME); } |
  identifier { $$ = tree_create($1, NULL, NODE_CLASS_NAME); }
  ;

/*
 * Structure content
 */
structure_content:
  structure_statements structure_initializer { $$ = tree_link_lists($1, $2); } |
  structure_statements
  ;

/*
 * Statements inside structure
 */
structure_statements:
  { $$ = NULL; } | 
  structure_statement structure_statements 
  { 
    //$$ = tree_create($1, $2, NODE_STMT_LIST); 
    $$ = tree_link_lists($1, $2);
  }
  ;

/*
 * Statement inside structure
 */
structure_statement:
  var_declaration /* Leave by default */ |
  structure_operator { $$ = tree_create($1, NULL, NODE_STMT_LIST); }
  ;

/*
 * TODO: There should be just regular operators
 */

structure_operator:
  pure_assign_operator |
  if_operator
  ;

/*
 * Structure initialization
 */
structure_initializer:
  TOK_BEGIN
    operator_list
  TOK_END
  { $$ = $2; }
  ;

/*
 * Single identifier
 */
identifier:
  TOK_IDENTIFIER { $$ = tree_create($1, NULL, NODE_IDENTIFIER); }
  ;
