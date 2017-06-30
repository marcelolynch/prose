./compiler/prose_compiler < $1 > compiled.c
gcc compiled.c -g runtime/*.c -o prose.out