#include <stdio.h>
#include <string.h>
#include "bigNumber.h"

typedef class BigNumber intxx;

int main(){
  char s[30000];
  char str_a[10000], str_b[10000];
    
  while(scanf("%s %s", str_a, str_b) == 2){
    if(strcmp(str_a, "exit") == 0)
      break;
    intxx a(str_a);
    intxx b(str_b);
    intxx c, d, e, f;
    c = a + b;
    c.print_line();
    d = a - b;
    d.print_line();
    e = a * b;
    e.print_line();
    f = a / b;
    f.print_line();
  }
  return 0;
} 
