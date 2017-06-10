#include "variable_manager.h"
#include "variable_arithmetics.h"
#include "prose_functions.h"
void main(void) { 

assign(0, anon_int(9));
assign(1, anon_int(19));
assign(2, anon_int(92));


if((compare(get_var(0), get_var(1)) == 0)){
print_var(anon_str("a es b"));
}
else if((compare(get_var(0), get_var(2)) == 0)){
print_var(var_sum(var_sum(var_sum(anon_str("a es "), get_var(0)), anon_str(", c es ")), get_var(2)));
} else if(1){
print_var(anon_str("else"));
} }
