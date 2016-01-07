ml: mpc.o parsing.o evaluation.o
	cc -o ml ml.c mpc.o parsing.o evaluation.o

mpc.o: mpc.h mpc.c
	cc -c mpc.c
parsing.o: parsing.h parsing.c
	cc -c parsing.c
evaluation.o: evaluation.h evaluation.c
	cc -c evaluation.c

clean:
	rm mpc.o parsing.o evaluation.o
