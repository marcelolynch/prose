#include <stdlib.h>
#include "runtime/include/variables.h"
#include "runtime/include/prose_arrays.h"
#include "runtime/include/prose_functions.h"
int main(void) {

map_name(0, "cadenaLoca");
map_name(1, "mutable");
map_name(2, "listaLoca");
map_name(3, "nadaQueVer");
assign(0, anon_str("HoLa coM0 tE v4 !!!"));
print_var(get_var(0), 1);
tolower_str(0);
print_var(get_var(0), 1);
toupper_str(0);
print_var(get_var(0), 1);
tolower_str(0);
print_var(get_var(0), 1);
toupper_str(0);
print_var(get_var(0), 1);
assign(1, anon_int(0));
print_var(get_var(1), 1);
inc(1);
print_var(get_var(1), 1);
dec(1);
print_var(get_var(1), 1);
append(0, anon_str("asdasd"));
print_var(get_var(0), 1);
assign(2, anon_arr(3, anon_str("asd"), anon_str("loco"), anon_int(12)));
print_var(get_var(2), 1);
append(2, anon_str("no tan loco"));
print_var(get_var(2), 1);
assign(3, anon_int(6));
append(3, anon_str("esto explota"));
}
