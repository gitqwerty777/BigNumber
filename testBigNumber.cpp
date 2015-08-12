#include <stdio.h>
#include <string.h>
#include "bigNumber.h"

typedef class BigNumber intxx;

char opchar[] = "+-*/><=";
void test(const char message[], const char as[], int op, const char bs[], const char anss[]){
  bool success;
  intxx a(as);
  intxx b(bs);
  intxx ans(anss);
  intxx c;
  switch(op){
  case 1:
    success = (c=a+b)==ans;
    break;
  case 2:
    success = (c=a-b)==ans;
    break;
  case 3:
    success = (c=a*b)==ans;
    break;
  case 4:
    success = (c=a/b)==ans;
    break;
  case 5:
    success = a>b;
    c=a-b;
    break;
  case 6:
    success = a<b;
    c=a-b;
    break;
  case 7:
    a = b;
    success = (a == ans);
    c = a;
    break;
  }
  if(!success)
    printf("%s:error\n%s\n%c\n%s\n=%s\nnot euqal to real ans\n%s\n", message, as, opchar[op-1], bs, c.getString().c_str(), anss);
  else
    printf("%s:ok\n", message);
}

int main(){
  char s[30000];
  char str_a[10000], str_b[10000];
  test("testbug", "1000000000000000000000", 2, "0099999999999999999999", "900000000000000000001");
  test("testadd:a>b", "1231231312312319989889", 1, "78974564894", "1231231312391294554783");
  test("testadd:a<b", "78978972654682", 1, "12311248634865145648", "12311327613837800330");
  test("testadd:carry", "78978972654682", 1, "78978972654682", "157957945309364");
  test("testadd:a, -b", "1000000000000000000000", 1, "-99999999999999999999", "900000000000000000001");
  test("testadd:-a, b", "-1000000000000000000000", 1, "99999999999999999999", "-900000000000000000001");

  test("testminus:a>b", "1000000000000000000000", 2, "99999999999999999999", "900000000000000000001");
  test("testminus:a<b", "1238975984710910122838", 2, "1923821081049374094910", "-684845096338463972072");

    test("testmultiply:a<b", "103879578945709798752985", 3, "18907897058957345489572097891", "1964144385233313691925661089990206594399282148454635");
    test("testmultiply:a>b", "817463911051237065638871237", 3, "178203017401374027401113208", "145674535566058868912774283061047456896075610371998296");
    test("testmultiply:zero", "817463911051237065638871237", 3, "0", "0");

    test("test divide: a>b", "18097970520781060531618", 4, "17892697842", "1011472427500");
    test("test divide: a<b", "17892697842", 4, "18097970520781060531618", "0");
    test("test divide: same length1 a=b", "18097970520781060531618", 4, "18097970520781060531618", "1");
    test("test divide: same length a>b", "18097970520791060531618", 4, "18097970520781060531618", "1");
    test("test divide: same length a>b", "18097970520781060531619", 4, "18097970520781060531618", "1");
    test("test divide: same length a<b", "18097970520781060531617", 4, "18097970520781060531618", "0");
    test("test divide: negative", "-180979705207810612377531617", 4, "909970520781060538", "-198885239");
    
    test("test divide by zero", "123213131231231230000000000", 4, "0", "0");//error

    test("test >", "123213131231231230000000000", 5, "123213111231231230000000000", "0");
    test("test >", "123213131231231230000000000", 5, "-123213111231231230000000000", "0");
    test("test <", "-123213131231231230000000000", 6, "123213111231231230000000000", "0");
    test("test <", "-123213131231231230000000000", 6, "-123213111231231230000000000", "0");

    test("test =", "123131231231231231", 7, "1122233344455", "1122233344455");

  return 0;
} 
