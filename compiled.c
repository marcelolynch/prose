#include <stdlib.h>
#include "runtime/include/variables.h"
#include "runtime/include/prose_arrays.h"
#include "runtime/include/prose_functions.h"
int main(void) { 

map_name(0, "lista");
map_name(1, "tam");
map_name(2, "i");
map_name(3, "j");
map_name(4, "minimo");
map_name(5, "aux");
assign(0, anon_arr(2, anon_int(1), anon_int(1)));
assign(0, anon_arr(10, anon_int(3), anon_int(4), anon_int(1), anon_int(2), anon_int(5), anon_int(10), anon_int(9), anon_int(8), anon_int(6), anon_int(7)));
assign(1, anon_int(10));
assign(2, anon_int(0));


while((compare(get_var(2), get_var(1)) < 0)){
assign(3, get_var(2));
assign(4, get_var(3));


while((compare(get_var(3), get_var(1)) < 0)){


if((compare(array_index(get_var(0), get_var(3)), array_index(get_var(0), get_var(4))) < 0)){
assign(4, get_var(3));
}
assign(3, var_sum(get_var(3), anon_int(1)));
}

assign(5, array_index(get_var(0), get_var(2)));
array_assign(get_var(0), get_var(2), array_index(get_var(0), get_var(4)));
array_assign(get_var(0), get_var(4), get_var(5));
assign(2, var_sum(get_var(2), anon_int(1)));
}

print_var(get_var(0), 1);
}
