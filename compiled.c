#include "variable_manager.h"
#include "variable_arithmetics.h"
#include "prose_functions.h"
void main(void) { 

assign(0, anon_int(9));
print_var(0);
assign(0, sum(anon_int(10), anon_float(1.7000000477)));
print_var(0);
assign(0, sum(anon_int(3), anon_str("Posta?")));
}
