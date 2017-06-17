#include "runtime/include/variables.h"
#include "runtime/include/prose_functions.h"
void main(void) { 

assign(0, anon_int(6));


while(!(compare(get_var(0), anon_int(0)) == 0)){
assign(0, var_sub(get_var(0), anon_int(1)));
print_var(var_sum(anon_str("a = "), get_var(0)), 1);


if((compare(get_var(0), anon_int(3)) == 0)){
print_var(anon_str("a vale 3!"), 1);
}
else if((compare(get_var(0), anon_int(5)) == 0)){
print_var(anon_str("a vale 5"), 1);
} else if(1){
print_var(anon_str("a no vale 3 ni 5"), 1);
} }

}
