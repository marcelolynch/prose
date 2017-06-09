#include "variable_manager.h"
#include "prose_functions.h"
float floatHolder;
int intHolder;
void main(void) { 

intHolder = 9;
(int)assign(0, &intHolder, INT_T);
print_var(0);
(char*)assign(0, "Hola chelooo", STR_T);
print_var(0);
(char*)assign(1, "Aja", STR_T);
print_var(1);
floatHolder = 12.800000;
(float)assign(1, &floatHolder, FLOAT_T);
print_var(1);
intHolder = 4;
(int)assign(0, &intHolder, INT_T);
intHolder = 4;
(int)assign(1, &intHolder, INT_T);


while((compare(0, 1) == 0)){
	print_var(0);
	intHolder = 5;
(int)assign(0, &intHolder, INT_T);
}

}
