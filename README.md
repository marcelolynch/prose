# Prose

## Compilación del compilador
`make all` dentro del directorio *compiler* generará el ejecutable *compiler/prose_compiler* correspondiente al compilador.
Con `make clean` se borran los archivos creados

## Compilación de un programa
Ejecutar `./compiler/prose_compiler < programa_prose.pr > compiled.c` dentro del directorio raíz generará el compilado *compiled.c* dentro del mismo; donde `programa_prose.pr` corresponde a un programa escrito en **prose**. Luego de esto debe compilarse el .c con el resto de los archivos del directorio `runtime`:
`gcc compiled.c runtime/*.c -o prose.out`. El archivo *prose.out* corresponde al ejecutable del programa.

## Scripts de compilación
Se proveen en el directorio raíz del proyecto dos scripts de automatización de los procesos mencionados: con *compile.sh* se genera el ejecutable final `prose.out` y el compilado a C `compiled.c`, y requiere que el binario del compilador se encuentre en `compiler/prose_compiler`. Basta con ejecutar `./compile.sh programa_prose.pr`. El script `make-compile.sh` además recompila el compilador (usando `make`) antes de invocar `compile.sh`. La invocación es análoga: `./compile.sh programa_prose.pr`.


## Ejecución de un programa
Ejecutar `./prose.out` dentro del directorio raíz


## Testing
Se pueden ejecutar los test-cases con ruby: `ruby test.rb`. El buen funcionamiento de este script depende de `compile.sh` y del Makefile del directorio `compiler`, luego sobreescribe tanto los archivos del compilador como `compiled.c` y `prose.out`.