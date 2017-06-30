# Prose

## Compilación del compilador
`make all` dentro del directorio *compiler* generará el ejecutable *compiler/prose_compiler* correspondiente al compilador

## Compilación de un programa
Ejecutar `./compiler/prose_compiler < <programa_prose.pr> > compiled.c` dentro del directorio raíz generará el ejecutable *prose.out* dentro del mismo; donde `<programa_prose.pr>` corresponde a un programa escrito en **prose**

## Script de Compilación
Se provee el script *compile.sh* dentro del directorio raíz que automatiza los pasos mencionados anteriormente. Basta con ejectur `./compile.sh <programa_prose.pr>`

## Ejecución de un programa
Ejecutar `./prose.out` dentro del directorio raíz
