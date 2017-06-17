cd compiler
make all

cd ..
./compiler/prose_compiler < $1 > compiled.c
gcc compiled.c runtime/*.c -o prose.out

cd compiler
make clean