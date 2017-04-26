#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "tree.h"
#include "generator.h"
#include "backend.h"

/*
 * Find all "orphan" statements (statements outside functions) 
 * and put them in init pseudo-function
 */
tree *create_init(tree *root)
{
  assert(root != NULL);

  tree *statements = NULL;
  tree *nroot = NULL; /* New root */

  /* 
   * First, search for "orphan" statements.
   * They are everything besides:
   * a) Class definition
   * b) Function definition
   * c) Type declaration
   * d) Extern declaration
   * e) Variable declaration
   * f) Constant declaration
   */
  tree *t = NULL;

  while (root != NULL)
  {
    t = root->next;
    root->next = NULL;

    assert(root->type == NODE_STMT_LIST);
    assert(root->value != NULL);
    
    switch (root->value->type)
    {
      case NODE_CLASS_DEF:
      case NODE_FUNC_DEF:
      case NODE_CLASS_DECL:
      case NODE_EXTERN_DECL:
      case NODE_VAR_DECL:
      case NODE_CONST_DECL:
        /* If it's what we want, just copy it to output */
        nroot = tree_link_lists(nroot, root);
        break;

      default:
        /* Copy to our statement list */
        statements = tree_link_lists(statements, root);
        break;
    }

    root = t;
  }

  /* Finally, create function and link it into tree */
  tree *id = tree_create(OP_INIT, NULL, NODE_IDENTIFIER);
  tree *name = tree_create(id, NULL, NODE_FUNC_NAME);
  tree *init = tree_create_ex(name, statements, NODE_FUNC_DEF, -1, NULL);
  tree *node = tree_create(init, NULL, NODE_STMT_LIST);

  return tree_link_lists(nroot, node);
}

/*
 * Rebuild classes:
 * 1) Create constructor and put orphan statements into there
 * 2) Link all methods into class they corresponds to
 * Returns new tree without methods (only functions)
 */
/*
 * Perform part 1: find and move orphan statements
 */
tree *rebuild_class_orphan(tree *class)
{
  assert(class->type == NODE_CLASS_DEF);

  tree *statements = NULL;
  tree *nroot = NULL; /* New root */
  tree *cname = class->left; /* Class name */
  tree *root = class->right; /* Statements */

  /* 
   * First, search for "orphan" statements.
   * They are everything else besides variable declaration.
   */
  tree *t = NULL;

  while (root != NULL)
  {
    t = root->next;
    root->next = NULL;

    assert(root->type == NODE_STMT_LIST);
    assert(root->value != NULL);
    
    if (root->value->type == NODE_VAR_DECL) 
      /* If it's variable declaration, just copy it to output */
      nroot = tree_link_lists(nroot, root);
    else {
      /* Copy to our statement list */
      statements = tree_link_lists(statements, root);
    }

    root = t;
  }

  /* Finally, create constructor and link it into tree */
  tree *name = tree_create(cname->left, cname->left, NODE_FUNC_NAME);
  tree *init = tree_create_ex(name, statements, NODE_FUNC_DEF, FTYPE_CONSTRUCTOR, NULL);
  tree *node = tree_create(init, NULL, NODE_STMT_LIST);
  nroot = tree_link_lists(nroot, node);

  /* Declarations go in place */
  class->right = nroot;

  return class;
}

/*
 * Find class by it's name
 */
tree *find_class_by_name(tree *root, char *name)
{
  while (root != NULL)
  {
    assert(root->type == NODE_STMT_LIST);

    //assert(root->value != NULL); /* Can be NULL if we deleted something

    if (root->value != NULL && root->value->type == NODE_CLASS_DEF)
    {
      tree *classs = root->value;

      assert (classs->left->type == NODE_CLASS_NAME);

      assert (classs->left->value != NULL);

      if (!strcmp(classs->left->value->value, name))
        return classs;
        
    }

    root = root->next;
  }

  return NULL;
}

/*
 * Perform tasks 1 and 2
 */
tree *rebuild_classes(tree *root)
{
  assert(root != NULL);

  tree *nroot = root;
  tree *t = NULL;

  /* Part 1: find orphan statements in classes and put them 
   * into constructor */
  while (nroot != NULL)
  {
    assert (nroot->type == NODE_STMT_LIST);

    assert (nroot->value != NULL);

    if (nroot->value->type == NODE_CLASS_DEF)
      nroot->value = rebuild_class_orphan(nroot->value);

    nroot = nroot->next;
  }
  /* Part 1 done */
  nroot = root;

  /* Part 2: find all function nodes and classes they correspond to.
   * If class cannot be found, create new one. 
   * To simplify things a bit, it's divided it two parts:
   * a) Move function to class, mark it's old position as NULL statement
   * b) Remove NULL statements */
  /* Part 2a: move functions */
  while (nroot != NULL)
  {
    assert (nroot->type == NODE_STMT_LIST);

    tree *func = nroot->value;

    assert (func != NULL);

    if (func->type == NODE_FUNC_DEF)
    {
      tree *name = func->left;

      assert (name != NULL);

      if (name->right != NULL) /* It's a method */
      {
        /* Remove from tree */
        nroot->value = NULL;
        tree *classs = find_class_by_name(root, name->right->value);

        if (classs == NULL)
        {
          /* Class not found, create one */
          tree *cname = tree_create(name->right, NULL, NODE_CLASS_NAME);
          classs = tree_create(cname, NULL, NODE_CLASS_DEF);
          t = tree_create(classs, NULL, NODE_STMT_LIST);
          root = tree_link_lists(root, t);
        }

        t = tree_create(func, NULL, NODE_STMT_LIST);
        classs->right = tree_link_lists(classs->right, t);
      }
    }

    nroot = nroot->next;
  }

  /* Part 2b: remove NULL statements */
  nroot = NULL;

  while (root != NULL)
  {
    assert(root->type == NODE_STMT_LIST);

    t = root->next;
    root->next = NULL;

    if (root->value == NULL)
      free(root);
    else
      nroot = tree_link_lists(nroot, root);

    root = t;
  }

  return nroot;

}

void backend_process(tree *root)
{
  /* Create initializer */
  root = create_init(root);
  /* Create constructor for classes */
  root = rebuild_classes(root);

  generate_program(stdout, root);
}

