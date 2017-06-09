#include "variable_manager.h"
#include "prose_functions.h"
float floatHolder;
int intHolder;
void main(void) { 

assign(0, anon_int(9));
print_var(0);
assign(0, anon_float(3.500000));
print_var(0);
assign(1, anon_str("Hola"));
print_var(1);
assign(2, anon_str("Deberia mostrarse una vez"));


while((compare(get_var(0), get_var(1)) == 0)){
	print_var(2);
	assign(0, anon_int(5));
}

}
