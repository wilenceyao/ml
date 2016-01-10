#ifndef evaluation_h
#define evaluation_h

#include <stdlib.h>
#include <string.h>

#include "mpc.h"
#include "parsing.h"


lval* lval_eval_sexpr(lval* v);
lval* lval_eval(lval* v);
lval* lval_take(lval* v, int i);
lval* lval_pop(lval* v, int i);
lval* builtin_op(lval* a, char* op);



#endif
