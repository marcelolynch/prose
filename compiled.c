#include <stdlib.h>
#include "runtime/include/variables.h"
#include "runtime/include/prose_arrays.h"
#include "runtime/include/prose_functions.h"
int main(void) { 

map_name(0, "listaLoca");
map_name(1, "resta");
assign(0, anon_arr(5, anon_int(1), anon_str("hola"), anon_float(90.20000), anon_str("como"), anon_str("vaaa")));
assign(1, var_sub(get_var(0), anon_arr(3, anon_float(90.20000), anon_str("com"), anon_str("vaaaaaa"))));
assign(1, var_sub(get_var(1), anon_int(1)));
assign(1, var_sub(get_var(1), anon_str("hola")));
assign(1, var_sub(get_var(1), anon_str("com")));
print_var(get_var(1), 1);
}
