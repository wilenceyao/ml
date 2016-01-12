# ml

minimal lisp interpreter written in C.

## Summary
A minimal lisp interpreter.

Implemented:
 * Grammar
 * Arithmetic expression
 * Error Handling
 * Builtin function: list, head, tail, eval

## Environment
 * CentOS 7 (3.10.0-123.el7.x86_64)
 * cmake 2.8.11
 * clang 3.4.2

## HOW TO
### clone and compile

```
git@github.com:WilenceYao/ml.git
cd ml
make
```

### run

```
./ml
ml version 0.0.1
Press Ctrl+c to Exit

ml> ( + 1 2.3)
3.3
ml> (/ 2 0)
Error: Division Zero
ml> eval (head {(+ 1 2) (+ 10 20)})
3
ml>
```

## TO DO
 * Functions

## Reference
 * [buildyourownlisp](http://www.buildyourownlisp.com/contents)
 * [mpc](https://github.com/orangeduck/mpc)

## License
Licensed under the MIT
