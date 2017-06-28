#include <stdlib.h>
#include "runtime/include/variables.h"
#include "runtime/include/prose_arrays.h"
#include "runtime/include/prose_functions.h"
int main(void) { 

print_var(anon_str("Antes de terminar"), 1);
exit(0);
print_var(anon_str("No se debería mostrar esto"), 1);
}
