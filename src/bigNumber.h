/**********************************************************************************/
/*   Usage:
     Some useful functions to deal with big integer number(the number which can't store by long long)
     1.transform other type(string, int, double...) into big number structure, or transform big number structure to string
     2.basic calculation(+, -, *, /)
     3.basic operation(=, >, <, ==, !=...)
     TODO:
     1.complex number
     2.additional mathmatical calculation, like %, ^
     3.improve execution speed
     4.input with calculation form, parse and output the answer
     Language: CPP
     Author: HCL, 2014/02/03 
*/
/**********************************************************************************/

#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>
using namespace std;

/*
 Known Bug:
 
 Known Issue:
 *    add NaN
 *    append -> insert
 *    前導0(test)
 *    performance and memory
 *    OPERATORs (+= , -= , *= , /=)
 NOW Progress:
 */

class BigNumber{
 public:
  BigNumber(){this->init("0");}
  template <class T> BigNumber(T);
  BigNumber(vector<int>&, int, bool);
  
  BigNumber operator+(BigNumber);//TODO: need const argument?
  BigNumber operator-(BigNumber);
  BigNumber operator-();//unary minus
  BigNumber operator*(BigNumber);
  BigNumber operator/(BigNumber&);
  BigNumber abs();

  template <class T> BigNumber operator=(T);
  bool operator>(BigNumber&);
  bool operator==(BigNumber&);
  bool operator>=(BigNumber& comp){return *this > comp || *this == comp;}
  bool operator!=(BigNumber& comp){return !(*this == comp);}
  bool operator<(BigNumber& comp){return !(*this >= comp);}
  bool isAbsSmaller(BigNumber& comp);
  bool isAbsGreater(BigNumber&);
  // TODO: +=, -=, *=, /=
  
  string getString();//get value in string type
  void print(){if(neg) putchar('-'); printf("%s", this->unsigned_string.c_str());}
  void print_line(){this->print(); puts("");}
  
 private:
  bool neg;
  string unsigned_string;
  int deg; //位數 //TODO: is it used?

  void reset_number(string);
  void init(string);

  void make_vector(vector<int>&, int);
  vector<int> vec1; //used in +, -
  vector<int> vec2; //used in *
  void make_vector1();
  void make_vector2();
  
  BigNumber minus(BigNumber&);
  BigNumber add(BigNumber&);
  int estimate(string tempt, vector<string>& mult);
  void divide(string ts, string ds, string& ans);
  void reverseSign();
  bool isAbsGeq(BigNumber&);

  static int strcmp_abs(string a, string b);
  static bool isStringAbsGreater(string a, string b);
  static bool isStringAbsGeq(string a, string b);
};

//Template classes need to have the method definitions inside the header file. <http://stackoverflow.com/questions/9191210/templates-and-separate-compilation>
#include "bigNumber.hpp"
  
#endif


