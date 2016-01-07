#ifndef evaluation_h
#define evaluation_h

#include <stdlib.h>
#include <string.h>

#include "mpc.h"

double eval_op(double x, char* op, double y);
double eval(mpc_ast_t* t);


#endif
