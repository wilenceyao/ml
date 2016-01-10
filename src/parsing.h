#ifndef parsing_h
#define parsing_h

#include <stdio.h>
#include <string.h>
#include "mpc.h"

typedef struct lval {
    int type;
    double num;

    char* err;
    char* sym;

    /* Children: Count and Pointer to a list of lval*  */
    int count;
    struct lval** cell;
} lval;

/* Enumeration of Possible lval Types */
enum { LVAL_NUM, LVAL_ERR, LVAL_SYM, LVAL_SEXPR };

/* Number type lval */
lval* lval_num(double x);
lval* lval_err(char* s);
lval* lval_sym(char* s);
lval* lval_sexpr(void);
void lval_print(lval* v);
void lval_println(lval* v);
void lval_expr_print(lval* v);
lval* lval_read_num(mpc_ast_t* t);
lval* lval_read(mpc_ast_t* t);
lval* lval_add(lval* v, lval* x);
void lval_del(lval* v);

#endif
