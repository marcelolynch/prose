#include <stdlib.h>
#include "runtime/include/variables.h"
#include "runtime/include/prose_arrays.h"
#include "runtime/include/prose_functions.h"
int main(void) { 

map_name(0, "numeroleido");
map_name(1, "texto_leido");
print_var(anon_str("Ingrese un numero"), 1);
scan(0, 0);
print_var(get_var(0), 1);
print_var(anon_str("Ingrese un texto"), 1);
scan(1, 1);
print_var(get_var(1), 1);
}
