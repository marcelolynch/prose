#include <stdlib.h>
#include "runtime/include/variables.h"
#include "runtime/include/prose_arrays.h"
#include "runtime/include/prose_functions.h"
void main(void) { 

VAR v;
map_name(0, "a");
assign(0, anon_str("holaaa"));
print_var(get_var(0), 1);
print_var(var_div(get_var(0), anon_int(2)), 1);
}
