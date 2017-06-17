cd compiler
make all
gcc -o prose_compiler y.tab.c ast.c lex.yy.c -ly


cd ..
./compiler/prose_compiler < $1 > compiled.c
gcc compiled.c runtime/*.c -o prose.out

cd compiler

rm prose_compiler
make clean