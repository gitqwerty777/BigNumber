#include <stdio.h>
#include "test.h"

int main(){
	char str_a[1000], str_b[1000];
	while(scanf("%s %s", str_a, str_b) == 2){
		intxx a(str_a);
		intxx b(str_b);
		
		intxx c, d, e, f; // no need to 括號？
		
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