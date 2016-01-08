#include "ml.h"


static char input[2048];

int main(int argc, char** argv) {
    mpc_parser_t* Number = mpc_new("number");
    mpc_parser_t* Operator = mpc_new("operator");
    mpc_parser_t* Expr = mpc_new("expr");    
    /* define language */
    mpca_lang(MPCA_LANG_DEFAULT,
    "                                                        \
        number  : /-?[0-9]+([.][0-9]+)?/ ;                   \
        operator: '+' | '-' | '*' | '/' | '%' ;              \
        expr    : <number> | '(' <operator> <expr>+ ')';     \
    ",
    Number, Operator, Expr);
    puts("ml version 0.0.1");
    puts("Press Ctrl+c to Exit\n");
    
    /* In a never ending loop */
    while(1) {
        fputs("ml> ", stdout);
        fgets(input, 2048, stdin);
        mpc_result_t r;
        if (mpc_parse("ml", input, Expr, &r)) {
            /* On Success Print the AST */
            /* mpc_ast_print(r.output); */
            lval result = eval(r.output);
            lval_print(result);
            mpc_ast_delete(r.output);
        } else {
            /* Otherwise Print the Error */
            printf("SyntaxError: invalid syntax\n");
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        } 
    }

    /* Undefine and Delete our Parsers */
    mpc_cleanup(4, Number, Operator, Expr);
    
    return 0;
}
