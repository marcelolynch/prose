#include "variable_manager.h"
#include "prose_functions.h"
float floatHolder;
int intHolder;
void main(void) { 

intHolder = 9;
assign(0, anon_var(&intHolder, INT_T));
print_var(0);
assign(0, anon_var("Hola", STR_T));
print_var(0);
assign(1, anon_var("Hola", STR_T));
print_var(1);
assign(2, anon_var("Deberia mostrarse una vez", STR_T));


while((compare(get_var(0), get_var(1)) == 0)){
	print_var(2);
	intHolder = 5;
assign(0, anon_var(&intHolder, INT_T));
}

}
