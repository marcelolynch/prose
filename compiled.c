#include <stdlib.h>
#include "runtime/include/variables.h"
#include "runtime/include/prose_arrays.h"
#include "runtime/include/prose_functions.h"
int main(void) { 

map_name(0, "z");
map_name(1, "x");
map_name(2, "y");
assign(0, anon_int(1));


while((is_equals(get_var(0), anon_int(1)))){
print_var(anon_str("Ingrese un numero"), 1);
scan(0, 1);


if((compare(get_var(1), anon_int(0)) <= 0)){
exit(0);
}


if((compare(get_var(1), anon_int(3)) < 0)){


if((is_equals(get_var(1), anon_int(1)))){
print_var(anon_str("No"), 1);
exit(0);
}
else if(1){
print_var(anon_str("Si"), 1);
exit(0);
} }


if((is_equals(var_sub(get_var(1), var_prod(anon_int(2), var_div(get_var(1), anon_int(2)))), anon_int(0)))){
print_var(anon_str("No, es divisible por 2"), 1);
exit(0);
}
assign(2, anon_int(1));


while((compare(var_prod(get_var(2), get_var(2)), get_var(1)) <= 0)){


if((is_equals(var_sub(get_var(1), var_prod(get_var(2), var_div(get_var(1), get_var(2)))), anon_int(0)))){
print_var(var_sum(anon_str("No: es divisible por "), get_var(2)), 1);
exit(0);
}
inc(2);
}

print_var(var_sum(get_var(1), anon_str(" es primo :)")), 1);
}

}
