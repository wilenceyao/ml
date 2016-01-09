#include "error.h"

lval lval_num(double x) {
    lval v;
    v.type = LVAL_NUM;
    v.num = x;
    return v;
}

lval lval_err(int x) {
    lval v;
    v.type = LVAL_ERR;
    v.err = x;
    return v;
}

void lval_print(lval v) {
    switch (v.type) {
        case LVAL_NUM:
            /* double or int */
            if((v.num-(int)v.num) < 1e-15 || \
                    (v.num-(int)v.num) < -0.999999999999999 ) {
                printf("%d\n", (int)v.num);
            } else {
                printf("%g\n", v.num);
            }
            break;
        case LVAL_ERR:
            switch (v.err) {
                case LERR_DIV_ZERO:
                    printf("Error: Division Zero");
                    break;
                case LERR_BAD_OP:
                    printf("Error: Invalid Operator");
                    break;
                case LERR_BAD_NUM:
                    printf("Error: Invalid Number");
                    break;
            }
            printf("\n");
            break;
    }
}
