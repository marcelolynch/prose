make all
gcc -o compiler y.tab.c lex.yy.c -ly
./compiler < $1 > compiled.c
gcc compiled.c prose_functions.c variable_manager.c -o prose.out
rm compiler
make clean