all:
	yacc -d grammar.y
	lex parser.l
	gcc -o compiler lex.yy.c y.tab.c -ly

clean:
	rm lex.yy.c
	rm y.tab.c
	rm y.tab.h