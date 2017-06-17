#include "runtime/include/variables.h"
#include "runtime/include/prose_functions.h"
void main(void) { 

assign(0, anon_str("str"));
assign(1, anon_int(3));
assign(2, anon_arr());
add_to_array(2, anon_int(1));
add_to_array(2, anon_int(2));
assign(3, anon_arr());
add_to_array(3, get_var(0));
add_to_array(3, get_var(1));
add_to_array(3, get_var(2));
print_var(get_var(3), 1);
assign(1, anon_int(4));
assign(0, anon_str("hola"));
assign(2, anon_float(1.8999999762));
print_var(get_var(3), 1);
print_var(get_var(2), 1);
}
