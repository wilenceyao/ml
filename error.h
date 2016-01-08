#ifndef error_h
#define error_h

#include <stdio.h>

typedef struct {
    int type;
    double num;
    int err;
} lval;

/* Enumeration of Possible lval Types */
enum { LVAL_NUM, LVAL_ERR };

/* Enumeration of Possible Error Types  */
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };

/* Number type lval */
lval lval_num(double x);
lval lval_err(int x);
void lval_print(lval v);



#endif
