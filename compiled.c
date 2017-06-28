#include <stdlib.h>
#include "runtime/include/variables.h"
#include "runtime/include/prose_arrays.h"
#include "runtime/include/prose_functions.h"
int main(void) { 

map_name(0, "saludo");
map_name(1, "restado");
assign(0, anon_str("hola como te va espero que muy bien!."));
assign(1, var_sub(get_var(0), anon_str("como ")));
assign(1, var_sub(get_var(1), anon_str("bien!.")));
assign(1, var_sub(get_var(1), anon_str("bie")));
print_var(get_var(1), 1);
}
