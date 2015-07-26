#include <stdio.h>
#include "bigNumber.h"

int main(){
  char s[30000];
  char str_a[10000], str_b[10000];
  while(scanf("%s %s", str_a, str_b) == 2){
    intxx a(str_a);
    intxx b(str_b);
    intxx c, d, e, f;

    puts("test1:");
    c = a + b;
    c.print_line();
    d = a - b;
    d.print_line();
    e = a * b;
    e.print_line();
    f = a / b;
    f.print_line();
    printf("test2:");
    a = "1000000000000000000000";
    b = "0099999999999999999999";
    c = a - b;
    c.print_line();
    d = "900000000000000000001";
    if(c != d){
      puts("error\n900000000000000000001 -> real ans");
    }
    else
      puts("complete");
  }
  return 0;
} 