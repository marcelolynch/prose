#include "variable_manager.h"
#include "variable_arithmetics.h"
#include "prose_functions.h"
void main(void) { 

assign(0, anon_int(0));
assign(1, anon_int(10));


while((compare(get_var(1), anon_int(0)) > 0)){
assign(1, var_sub(get_var(1), anon_int(1)));
assign(0, var_sum(get_var(0), get_var(1)));
}

print_var(get_var(0), 1);
print_var(anon_str("Hola mundo"), 1);
print_var(anon_str("Hola mundo"), 1);
}
