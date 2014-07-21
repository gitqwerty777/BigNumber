#include <stdio.h>
#include "test.h"

int main(){
	char str_a[10000], str_b[10000];
	while(scanf("%s %s", str_a, str_b) == 2){
		intxx a(str_a);
		intxx b(str_b);
		
		intxx c, d, e, f; // no need to 括號？
		
		c = a + b;
		printf("+ = "); c.print_line();
		d = a - b;
		printf("- = "); d.print_line();
		e = a * b;
		printf("* = "); e.print_line();
		f = a / b;
		printf("/ = "); f.print_line();
	}
	return 0;
} 