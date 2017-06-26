#include <stdlib.h>
#include "runtime/include/variables.h"
#include "runtime/include/prose_arrays.h"
#include "runtime/include/prose_functions.h"
void main(void) { 

map_name(0, "hola");
assign(0, anon_arr(2, anon_float(1.00000), anon_int(3)));
print_var(var_sum(get_var(0), anon_float(2.00000)), 1);
print_var(var_sum(anon_float(2.00000), anon_float(1.30000)), 1);
}
