main: main.o lex.o syn.o
	cc -g lex.o syn.o main.o -o main

main.o: main.c main.h syn.h
	cc -g -c -o main.o main.c

lex.c: lex.l
	flex  -o lex.c lex.l

lex.o: lex.c syn.h main.h
	cc -g -c -o lex.o lex.c

syn.c syn.h: syn.y
	bison syn.y -d -o syn.c

syn.o: syn.c syn.h main.h
	cc -g -c -o syn.o syn.c

PHONY: clean

clean:
	rm -f *.o lex.c syn.c syn.h main
