#ifndef evaluation_h
#define evaluation_h

#include <stdlib.h>
#include <string.h>

#include "mpc.h"
#include "error.h"

lval eval_op(lval x, char* op, lval y);
lval eval(mpc_ast_t* t);


#endif
