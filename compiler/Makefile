all:
	yacc -d grammar.y
	lex parser.l
	gcc -Wall -o prose_compiler y.tab.c ast.c lex.yy.c -ly

clean:
	rm prose_compiler
	rm lex.yy.c
	rm y.tab.c
	rm y.tab.h