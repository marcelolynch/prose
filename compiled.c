#include "variable_manager.h"
#include "variable_arithmetics.h"
#include "prose_functions.h"
void main(void) { 

assign(0, anon_int(9));
assign(1, anon_int(1));
assign(2, anon_int(2));


while(!(compare(get_var(0), anon_int(0)) == 0)){
assign(0, var_sub(get_var(0), anon_int(1)));
print_var(var_sum(anon_str("a = "), get_var(0)));


if((compare(get_var(0), anon_int(3)) == 0)){
print_var(anon_str("a vale 3!"));
}
else if((compare(get_var(0), anon_int(5)) == 0)){
print_var(anon_str("a vale 5"));
} else if(1){
print_var(anon_str("a no vale 3 ni 5"));
} }

}
