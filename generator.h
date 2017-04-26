#ifndef __GENERATOR_H__
#define __GENERATOR_H__

/*
 * Generation procedures
 */

#include "tree.h"

void generate_var_decl(FILE *output, tree *node, int level);
void generate_var_decl_stmt(FILE *output, tree *node, int level);
void generate_identifier(FILE *output, tree *node, int level);
void generate_const_decl(FILE *output, tree *node, int level);
void generate_const_use(FILE *output, tree *node, int level);
void generate_return(FILE *output, tree *node, int level);
void generate_break(FILE *output, tree *node, int level);
void generate_var_use(FILE *output, tree *node, int level);
void generate_function_def(FILE *output, tree *node, int level);
void generate_function_head(FILE *output, tree *node, int level);
void generate_function_call(FILE *output, tree *node, int level);
void generate_meth_invoke(FILE *output, tree *node, int level);
void generate_class_def(FILE *output, tree *node, int level);
void generate_class_decl(FILE *output, tree *node, int level);
void generate_class_head(FILE *output, tree *node, int level);
void generate_class_impl(FILE *output, tree *node, int level);
void generate_statement_list(FILE *output, tree *node, int level);
void generate_until(FILE *output, tree *node, int level);
void generate_while(FILE *output, tree *node, int level);
void generate_for(FILE *output, tree *node, int level);
void generate_if(FILE *output, tree *node, int level);
void generate_expression(FILE *output, tree *node, int level);
void generate_expression_protect(FILE *output, tree *node, int level, int c);
void generate_expression_unprotected(FILE *output, tree *node, int level);
void generate_assign(FILE *output, tree *node, int level);
void make_indent(FILE *output, int level);
void generate_program(FILE *output, tree *node);

#endif // __GENERATOR_H__
