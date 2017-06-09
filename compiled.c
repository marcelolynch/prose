#include "variable_manager.h"
#include "prose_functions.h"
float floatHolder;
int intHolder;
void main(void) { 

intHolder = 9;
(int)assign(0, &intHolder, INT_T);
print_var(0);
(char*)assign(0, "Hola", STR_T);
print_var(0);
(char*)assign(1, "Hola", STR_T);
print_var(1);
(char*)assign(2, "Deberia mostrarse una vez", STR_T);


while((compare(0, 2) == 0)){
	print_var(2);
	intHolder = 5;
(int)assign(0, &intHolder, INT_T);
}

}
