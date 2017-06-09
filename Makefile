all:
	yacc -d grammar.y
	lex parser.l
	gcc -g -o compiler lex.yy.c ast.c y.tab.c -ly

clean:
	rm lex.yy.c
	rm y.tab.c
	rm y.tab.h