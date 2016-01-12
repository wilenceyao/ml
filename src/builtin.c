#include "builtin.h"

#define LASSERT(args, cond, err) \
    if (!(cond)) { lval_del(args); return lval_err(err); }

lval* builtin_head(lval* a) {
    /* head need only list*/
    LASSERT(a, a->count == 1,
        "Function 'head' passed too many arguments!");
    LASSERT(a, a->cell[0]->type == LVAL_QEXPR,
        "Function 'head' passed incorrect type!");
    LASSERT(a, a->cell[0]->count != 0,
        "Function 'head' passed {}!");

    lval* v = lval_take(a, 0);  
    while (v->count > 1) { lval_del(lval_pop(v, 1)); }
    return v;

}


lval* builtin_tail(lval* a) {
    LASSERT(a, a->count == 1,
        "Function 'tail' passed too many arguments!");
    LASSERT(a, a->cell[0]->type == LVAL_QEXPR,
        "Function 'tail' passed incorrect type!");
    LASSERT(a, a->cell[0]->count != 0,
        "Function 'tail' passed {}!");

    lval* v = lval_take(a, 0);  
    lval_del(lval_pop(v, 0));
    return v;
}


lval* builtin_list(lval* a) {
    a->type = LVAL_QEXPR;
    return a;
}


lval* builtin_eval(lval* a) {
    LASSERT(a, a->count == 1,
        "Function 'eval' passed too many arguments!");
    LASSERT(a, a->cell[0]->type == LVAL_QEXPR,
        "Function 'eval' passed incorrect type!");

    lval* x = lval_take(a, 0);
    x->type = LVAL_SEXPR;
    return lval_eval(x);
}


lval* builtin_join(lval* a) {
    for (int i = 0; i < a->count; i++) {
        LASSERT(a, a->cell[i]->type == LVAL_QEXPR,
            "Function 'join' passed incorrect type.");
    }

    lval* x = lval_pop(a, 0);

    while (a->count) {
        x = lval_join(x, lval_pop(a, 0));
    }

    lval_del(a);
    return x;
}


lval* builtin_op(lval* a, char* op) {
    /* Ensure all arguments are numbers */
    for (int i = 0; i < a->count; i++) {
        if (a->cell[i]->type != LVAL_NUM) {
            lval_del(a);
            return lval_err("Cannot operate on non-number!");
        }
    }

    /* Pop the first element */
    lval* x = lval_pop(a, 0);

    /* If no arguments and sub then perform unary negation */
    if ((strcmp(op, "-") == 0) && a->count == 0) {
        x->num = -x->num;
    }

    /* While there are still elements remaining */
    while (a->count > 0) {
        lval* y = lval_pop(a, 0);

        if (strcmp(op, "+") == 0) { x->num += y->num; }
        if (strcmp(op, "-") == 0) { x->num -= y->num; }
        if (strcmp(op, "*") == 0) { x->num *= y->num; }
        if (strcmp(op, "/") == 0) {
            if (y->num == 0) {
                lval_del(x); lval_del(y);
                x = lval_err("Division By Zero!");
                break;
            }
            x->num /= y->num;
        }
        if (strcmp(op, "%") == 0){
            return lval_num((int)x->num % (int)y->num);
        }

        lval_del(y);
    }

    lval_del(a);
    return x;
}


lval* builtin(lval* a, char* func) {
    if (strcmp("list", func) == 0) { return builtin_list(a); }
    if (strcmp("head", func) == 0) { return builtin_head(a); }
    if (strcmp("tail", func) == 0) { return builtin_tail(a); }
    if (strcmp("join", func) == 0) { return builtin_join(a); }
    if (strcmp("eval", func) == 0) { return builtin_eval(a); }
    if (strstr("+-/*", func)) { return builtin_op(a, func); }
    
    lval_del(a);
    return lval_err("Unknown Function!");
}
