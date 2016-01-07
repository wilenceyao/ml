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

double eval_op(double x, char* op, double y) {
    if (strcmp(op, "+") == 0) { return x + y; }
    if (strcmp(op, "-") == 0) { return x - y; }
    if (strcmp(op, "*") == 0) { return x * y; }
    if (strcmp(op, "/") == 0) { return x / y; }
    if (strcmp(op, "%") == 0) { return (int)x % (int)y; }

    return 0;
}

double eval(mpc_ast_t* t) {
    if (strstr(t->tag, "number")) {
        return atof(t->contents);
    }

    char* op = t->children[1]->contents;
    /* children[0] is '('*/
    double x = eval(t->children[2]);

    int i = 3;
    while (strstr(t->children[i]->tag, "expr")) {
        x = eval_op(x, op, eval(t->children[i]));
        i++;
    }
    return x;
}
