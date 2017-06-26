#include <stdlib.h>
#include "runtime/include/variables.h"
#include "runtime/include/prose_arrays.h"
#include "runtime/include/prose_functions.h"
void main(void) { 

map_name(0, "a");
map_name(1, "b");
assign(0, anon_int(4));
assign(1, var_sum(get_var(0), anon_int(2)));


if((compare(get_var(0), get_var(1)) < 0)){
print_var(get_var(0), 1);
}
assign(0, anon_int(4));
assign(1, var_sum(get_var(0), anon_int(2)));


if((compare(get_var(0), get_var(1)) < 0)){
print_var(get_var(0), 1);
}
}
