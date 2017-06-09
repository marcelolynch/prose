#include "variable_manager.h"
#include "variable_arithmetics.h"
#include "prose_functions.h"
void main(void) { 

assign(0, anon_int(9));
print_var(0);
assign(0, sum(anon_int(10), anon_float(1.7000000477)));
print_var(0);
assign(0, sum(anon_int(3), anon_str("Posta?")));
print_var(0);
assign(1, sum(sum(sum(anon_str("La precedencia a izquierda hace esto: "), anon_int(9)), anon_int(9)), anon_float(19.7999992371)));
print_var(1);
assign(0, anon_int(4));
assign(2, anon_int(5));


while((compare(get_var(0), get_var(2)) == 0)){
	print_var(1);
	assign(0, anon_int(5));
}

}
