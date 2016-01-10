#include "parsing.h"

lval* lval_num(double x) {
    lval* v = malloc(sizeof(lval));
    v->type = LVAL_NUM;
    v->num = x;
    return v;
}


lval* lval_err(char* s) {
    lval *v = malloc(sizeof(lval));
    v->type = LVAL_ERR;
    v->err = malloc(strlen(s) + 1);
    strcpy(v->err, s);
    return v;
}


lval* lval_sym(char* s) {
    lval* v = malloc(sizeof(lval));
    v->type = LVAL_SYM;
    v->sym = malloc(strlen(s) + 1);
    strcpy(v->sym, s);
    return v;
}


lval* lval_sexpr(void) {
    lval* v = malloc(sizeof(lval));
    v->type = LVAL_SEXPR;
    v->count = 0;
    /* lval* cel */
    v->cell = NULL;
    return v;
}


void lval_print(lval* v) {
    switch (v->type) {
        case LVAL_NUM:
            /* double or int */
            if(((int)v->num - v->num) < 1e-15 && \
                     ((int)v->num - v->num) > -1e-15 ) {
                printf("%d", (int)v->num);
            } else {
                printf("%g", v->num);
            }
            break;
        case LVAL_ERR:
            printf("Error: %s", v->err);
            break;
        case LVAL_SYM:
            printf("%s", v->sym);
            break;
        case LVAL_SEXPR:
            lval_expr_print(v);
            break;
    }
}


void lval_println(lval* v) {
    lval_print(v);
    printf("\n");
}


void lval_expr_print(lval* v) {
    for (int i = 0; i < v->count; i++) {
        lval_print(v->cell[i]);

        if (i != v->count-1) {
            putchar(' ');
        }
    }
}


lval* lval_read_num(mpc_ast_t* t) {
    errno = 0;
    double x = atof(t->contents);
    return errno != ERANGE ? lval_num(x) : lval_err("invalid number");

}


lval* lval_read(mpc_ast_t* t) {
    if (strstr(t->tag, "number")) { return lval_read_num(t); }
    if (strstr(t->tag, "symbol")) { return lval_sym(t->contents); }

    /* root (>) or sexpr */
    lval* x = NULL;
    if (strcmp(t->tag, ">") == 0) { x = lval_sexpr(); }
    if (strstr(t->tag, "sexpr")) { x = lval_sexpr(); }

    for (int i = 0; i<t->children_num; i++) {
        if (strcmp(t->children[i]->contents, "(") == 0) { continue; }
        if (strcmp(t->children[i]->contents, ")") == 0) { continue; }
        if (strcmp(t->children[i]->tag,  "regex") == 0) { continue; }

        /* Add children to array cell */
        x = lval_add(x, lval_read(t->children[i]));
    }

    return x;
}


lval* lval_add(lval* v, lval* x) {
    v->count++;
    v->cell = realloc(v->cell, sizeof(lval) * v->count);
    v->cell[v->count-1] = x;
    return v;
}


void lval_del(lval* v) {
    switch (v->type) {
        case LVAL_NUM:
            break;
        case LVAL_ERR:
            free(v->err);
            break;
        case LVAL_SYM:
            free(v->sym);
            break;
        case LVAL_SEXPR:
            for (int i = 0; i < v->count; i++) {
                lval_del(v->cell[i]);
            }
            free(v->cell);
            break;
    }
    free(v);
}
