#include "variable_manager.h"
#include "variable_arithmetics.h"
#include "prose_functions.h"
void main(void) { 

assign(0, anon_arr());
array_add(0, anon_int(6));
array_add(0, anon_int(7));
array_add(0, anon_str("hola"));
assign(1, anon_arr());
array_add(1, anon_int(10));
array_add(1, get_var(0));
print_var(get_var(1), 1);
}
