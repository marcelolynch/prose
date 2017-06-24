#include <stdlib.h>
#include "runtime/include/variables.h"
#include "runtime/include/prose_arrays.h"
#include "runtime/include/prose_functions.h"
void main(void) { 

VAR v;
map_name(0, "a");
map_name(1, "b");
assign(0, anon_int(4));
print_var(get_var(0), 1);
assign(1, anon_arr(5, anon_int(10), anon_int(1), anon_arr(2, anon_int(2), anon_int(4)), anon_int(3), anon_int(5)));
print_var(get_var(1), 1);
array_assign(get_var(1), anon_int(1), anon_int(3));print_var(get_var(1), 1);
}
