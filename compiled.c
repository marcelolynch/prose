#include "variable_manager.h"
#include "variable_arithmetics.h"
#include "prose_functions.h"
void main(void) { 

assign(0, anon_int(9));
print_var(get_var(0));
assign(0, sum(anon_int(10), anon_float(1.7000000477)));
print_var(get_var(0));
assign(0, anon_int(3));
print_var(sum(get_var(0), anon_int(45)));
assign(1, sum(sum(sum(sum(sum(anon_str("carlu "), sum(anon_int(8), anon_float(1.9900000095))), anon_str(" ")), sum(anon_int(9), anon_int(9))), anon_str(" ")), sum(anon_int(1), anon_int(0))));
print_var(get_var(1));
assign(0, anon_int(4));
assign(2, anon_int(4));


while((compare(get_var(0), get_var(2)) == 0)){
	print_var(get_var(1));
	assign(0, anon_int(5));
}

}
