#include "ml.h"


static char input[2048];

int main(int argc, char** argv) {
    mpc_parser_t* Number = mpc_new("number");
    mpc_parser_t* Symbol = mpc_new("symbol");
    mpc_parser_t* Sexpr = mpc_new("sexpr");
    mpc_parser_t* Expr = mpc_new("expr");
    mpc_parser_t* Ml = mpc_new("ml");
    /* define language */
    mpca_lang(MPCA_LANG_DEFAULT,
    "                                                        \
        number  : /-?[0-9]+([.][0-9]+)?/ ;                   \
        symbol  : '+' | '-' | '*' | '/' | '%' ;              \
        sexpr   : '(' <expr>* ')' ;                          \
        expr    : <number> | <symbol> | <sexpr> ;            \
        ml      : /^/ <expr>*   /$/ ;                        \
    ",
    Number, Symbol, Sexpr, Expr, Ml);
    puts("ml version 0.0.1");
    puts("Press Ctrl+c to Exit\n");
    
    /* In a never ending loop */
    while(1) {
        fputs("ml> ", stdout);
        fgets(input, 2048, stdin);
        mpc_result_t r;
        if (mpc_parse("ml", input, Ml, &r)) {
            // mpc_ast_print(r.output);
            lval* x = lval_eval(lval_read(r.output));
            lval_println(x);
            lval_del(x);
            mpc_ast_delete(r.output);
        } else {
            /* Print the Error */
            printf("SyntaxError: invalid syntax\n");
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        } 
    }

    /* Undefine and Delete our Parsers */
    mpc_cleanup(5, Number, Symbol, Sexpr, Expr, Ml);
    
    return 0;
}
