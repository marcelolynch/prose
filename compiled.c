#include <stdlib.h>
#include "runtime/include/variables.h"
#include "runtime/include/prose_arrays.h"
#include "runtime/include/prose_functions.h"
void main(void) { 

VAR convenientVar;assign(0, anon_int(1));
convenientVar = anon_arr(NULL);
array_add(convenientVar.value.arrValue, get_var(0));
array_add(convenientVar.value.arrValue, get_var(0));
assign(0, convenientVar);
free_var_resources(&convenientVar);
print_var(get_var(0), 1);
convenientVar = anon_arr(NULL);
array_add(convenientVar.value.arrValue, get_var(0));
array_add(convenientVar.value.arrValue, get_var(0));
assign(0, convenientVar);
free_var_resources(&convenientVar);
print_var(get_var(0), 1);
}
