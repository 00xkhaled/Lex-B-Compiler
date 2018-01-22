compileAndRun: compile run

compile: batata.l  batata.y
	bison -d batata.y
	flex batata.l
	gcc -ll interpreter.c funcTable.c lex.yy.c batata.tab.c

bison: batata.y
	bison -d batata.y

flex: batata.l batata.tab.h
	flex batata.l

clean: lex.yy.c batata.tab.h batata.tab.c a.out
	rm lex.yy.c batata.tab.h batata.tab.c a.out

run: a.out
	./a.out
