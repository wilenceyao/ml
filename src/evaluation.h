#ifndef evaluation_h
#define evaluation_h

#include <stdlib.h>
#include <string.h>

#include "mpc.h"
#include "parsing.h"
#include "builtin.h"


lval* lval_eval_sexpr(lval* v);
lval* lval_eval(lval* v);



#endif
