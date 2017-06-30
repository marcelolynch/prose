#include <stdlib.h>
#include "runtime/include/variables.h"
#include "runtime/include/prose_arrays.h"
#include "runtime/include/prose_functions.h"
int main(void) { 

print_var(var_div(anon_str("abcdef"), anon_int(3)), 1);
}
