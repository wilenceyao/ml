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


lval* lval_eval_sexpr(lval* v){
    /* Children, recursion */
    for (int i = 0; i < v->count; i++) {
        v->cell[i] = lval_eval(v->cell[i]);
        if (v->cell[i]->type == LVAL_ERR) {
            return lval_take(v, i);
        }
    }

    /* Empty expresion */
    if (v->count == 0) {
        return v;
    }

    if (v->count == 1) {
        return lval_take(v, 0);
    }

    /* Ensure First Element is Symbol */
    lval* f = lval_pop(v, 0);
    if (f->type != LVAL_SYM) {
        lval_del(f);
        lval_del(v);
        return lval_err("Not start with symbol!");
    }

    /* Call builtin with operator */
    lval* result = builtin(v, f->sym);
    lval_del(f);
    return result;
}


lval* lval_eval(lval* v) {
    /* Evaluate Sexpressions */
    if (v->type == LVAL_SEXPR) { return lval_eval_sexpr(v); }

    /* All other lval types remain the same */
    return v;
}
