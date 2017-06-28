#include <stdlib.h>
#include "runtime/include/variables.h"
#include "runtime/include/prose_arrays.h"
#include "runtime/include/prose_functions.h"
int main(void) { 

map_name(0, "tablero");
map_name(1, "ganador");
map_name(2, "jugador");
map_name(3, "fila");
map_name(4, "columna");
map_name(5, "indice");
assign(0, anon_arr(3, anon_arr(3, anon_str("_"), anon_str("_"), anon_str("_")), anon_arr(3, anon_str("_"), anon_str("_"), anon_str("_")), anon_arr(3, anon_str("_"), anon_str("_"), anon_str("_"))));
assign(1, var_minus(anon_int(1)));
assign(2, anon_int(0));


while((compare(get_var(1), var_minus(anon_int(1))) == 0)){
assign(3, var_minus(anon_int(1)));
assign(4, var_minus(anon_int(1)));


while(!((compare(get_var(3), anon_int(0)) >= 0) && (compare(get_var(3), anon_int(3)) < 0))){
print_var(var_sum(anon_str("Seleccione Fila - Jugador "), get_var(2)), 1);
scan(0, 3);
}



while(!((compare(get_var(4), anon_int(0)) >= 0) && (compare(get_var(4), anon_int(3)) < 0))){
print_var(var_sum(anon_str("Seleccione Columna - Jugador "), get_var(2)), 1);
scan(0, 4);
}



if((compare(array_index(array_index(get_var(0), get_var(3)), get_var(4)), anon_str("_")) == 0)){
array_assign(array_index(get_var(0), get_var(3)), get_var(4), get_var(2));assign(5, anon_int(0));


while((compare(get_var(5), anon_int(3)) < 0)){


if((((compare(array_index(array_index(get_var(0), get_var(5)), anon_int(0)), get_var(2)) == 0) && (compare(array_index(array_index(get_var(0), get_var(5)), anon_int(1)), get_var(2)) == 0)) && (compare(array_index(array_index(get_var(0), get_var(5)), anon_int(2)), get_var(2)) == 0))){
assign(1, get_var(2));
}


if((((compare(array_index(array_index(get_var(0), anon_int(0)), get_var(5)), get_var(2)) == 0) && (compare(array_index(array_index(get_var(0), anon_int(1)), get_var(5)), get_var(2)) == 0)) && (compare(array_index(array_index(get_var(0), anon_int(2)), get_var(5)), get_var(2)) == 0))){
assign(1, get_var(2));
}
inc(5);
}



if((((compare(array_index(array_index(get_var(0), anon_int(0)), anon_int(0)), get_var(2)) == 0) && (compare(array_index(array_index(get_var(0), anon_int(1)), anon_int(1)), get_var(2)) == 0)) && (compare(array_index(array_index(get_var(0), anon_int(2)), anon_int(2)), get_var(2)) == 0))){
assign(1, get_var(2));
}


if((((compare(array_index(array_index(get_var(0), anon_int(0)), anon_int(2)), get_var(2)) == 0) && (compare(array_index(array_index(get_var(0), anon_int(1)), anon_int(1)), get_var(2)) == 0)) && (compare(array_index(array_index(get_var(0), anon_int(2)), anon_int(0)), get_var(2)) == 0))){
assign(1, get_var(2));
}
assign(2, var_sub(anon_int(1), get_var(2)));
}
else if(1){
print_var(anon_str("Ese lugar ya está ocupado!"), 1);
} print_var(array_index(get_var(0), anon_int(0)), 1);
print_var(array_index(get_var(0), anon_int(1)), 1);
print_var(array_index(get_var(0), anon_int(2)), 1);
}

print_var(var_sum(anon_str("El ganador fue el jugador "), get_var(1)), 1);
}
