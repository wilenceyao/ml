#ifndef builtin_h
#define builtin_h

#include <string.h>
#include <stdlib.h>

#include "parsing.h"
#include "evaluation.h"
#include "mpc.h"
#include "parsing.h"

lval* builtin_head(lval* a);
lval* builtin_tail(lval* a);
lval* builtin_list(lval* a);
lval* builtin_eval(lval* a);
lval* builtin_join(lval* a);
lval* builtin_op(lval* a, char* op);
lval* builtin(lval* a, char* func);



#endif
