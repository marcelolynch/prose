#include "variable_manager.h"
#include "prose_functions.h"
float floatHolder;
int intHolder;
void main(void) { 

intHolder = 9;
assign(0, &intHolder, INT_T);
print_var(0);
assign(0, "Hola chelooo", STR_T);
print_var(0);
}