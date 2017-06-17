cd compiler
make all

cd ..
./compiler/prose_compiler < $1 > compiled.c
gcc compiled.c -g runtime/*.c -o prose.out

cd compiler
make clean