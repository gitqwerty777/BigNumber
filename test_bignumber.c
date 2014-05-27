#include <stdio.h>
#include "test.h"

int main(){
	char str_a[1000], str_b[1000];
	while(scanf("%s %s", str_a, str_b) == 2){
		intxx a(str_a);
		intxx b(str_b);
		//a.print_number();
		//b.print_number();

		intxx c; // no need to 括號？
		intxx d;
		intxx e;
		intxx f;

		c = a + b;
		c.print_number_oneline();
		d = a - b;
		d.print_number_oneline();
		e = a * b;
		e.print_number_oneline();
		f = a / b;
		f.print_number_oneline();		
	}
	return 0;
} 