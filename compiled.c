#include <stdlib.h>
#include "runtime/include/variables.h"
#include "runtime/include/prose_arrays.h"
#include "runtime/include/prose_functions.h"
void main(void) { 

VAR v;
map_name(0, "a");
map_name(1, "b");
v = anon_arr(NULL);
array_push(v.value.arrValue, anon_int(1));
array_push(v.value.arrValue, anon_int(2));
array_push(v.value.arrValue, anon_int(3));
array_push(v.value.arrValue, anon_int(4));
assign(0, v);
free_var_resources(&v);
v = anon_arr(NULL);
array_push(v.value.arrValue, anon_int(6));
array_push(v.value.arrValue, anon_int(7));
assign(1, v);
free_var_resources(&v);
print_var(var_sum(get_var(0), get_var(1)), 1);
}
