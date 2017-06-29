#include <stdlib.h>
#include "runtime/include/variables.h"
#include "runtime/include/prose_arrays.h"
#include "runtime/include/prose_functions.h"
int main(void) { 

print_var(var_sum(var_sum(anon_str("hola"), anon_int(2)), var_sum(anon_int(6), anon_int(4))), 1);
}
