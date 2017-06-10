make all
gcc -o compiler y.tab.c ast.c lex.yy.c -ly
./compiler < $1 > compiled.c
gcc compiled.c prose_functions.c variable_manager.c variable_arithmetics.c prose_arrays.c -o prose.out
rm compiler
make clean