#include "evaluation.h"


/*
 * typedef struct mpc_ast_t {
 *   char* tag;
 *   char* contents;
 *   mpc_state_t state;
 *   int children_num;
 *   struct mpc_ast_t** children;
 * } 
 */ 

lval eval_op(lval x, char* op, lval y) {

    /* value is error */
    if (x.type == LVAL_ERR) { return x; }
    if (y.type == LVAL_ERR) { return y;}

    if (strcmp(op, "+") == 0) { return lval_num(x.num + y.num); }
    if (strcmp(op, "-") == 0) { return lval_num(x.num - y.num); }
    if (strcmp(op, "*") == 0) { return lval_num(x.num * y.num); }
    if (strcmp(op, "/") == 0) {
        return y.num ==0
            ?lval_err(LERR_DIV_ZERO)
            :lval_num(x.num / y.num);
    }
    if (strcmp(op, "%") == 0) { return lval_num((int)x.num % (int)y.num); }

    return lval_err(LERR_BAD_OP);
}

lval eval(mpc_ast_t* t) {
    if (strstr(t->tag, "number")) {
        /* ERANGE macro */
        errno = 0;
        double x = atof(t->contents);
        return errno != ERANGE ? lval_num(x) : lval_err(LERR_BAD_NUM);
    }
    /* children[0] is '('*/
    char* op = t->children[1]->contents;

    lval x = eval(t->children[2]);

    int i = 3;
    while (strstr(t->children[i]->tag, "expr")) {
        x = eval_op(x, op, eval(t->children[i]));
        i++;
    }
    return x;
}
