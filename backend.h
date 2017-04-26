#ifndef __BACKEND_H__
#define __BACKEND_H__

/*
 * Backend
 */

void backend_process(tree *root);

// HACK: definition for operation dispatcher
#define OP_DISPATCHER "op_dispatcher"
// HACK: definition for init pseudo-function
#define OP_INIT "op_init"

#endif // __BACKEND_H__
