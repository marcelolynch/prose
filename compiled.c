#include <stdlib.h>
#include "runtime/include/variables.h"
#include "runtime/include/prose_arrays.h"
#include "runtime/include/prose_functions.h"
int main(void) { 

map_name(0, "arreglo");
assign(0, anon_arr(1, anon_int(1)));
assign(0, var_sum(get_var(0), anon_int(2)));
assign(0, var_sum(get_var(0), anon_int(3)));
assign(0, var_sum(get_var(0), anon_arr(2, anon_int(4), anon_int(5))));
assign(0, var_sum(get_var(0), anon_str("Hola")));
print_var(get_var(0), 1);
}
