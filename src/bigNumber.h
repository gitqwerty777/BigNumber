/**********************************************************************************/
/*   Usage:
     Some useful functions to deal with big integer number(the number which can't store by long long)
     1.transform other type(string, int, double...) into big number structure, or transform big number structure to string
     2.basic calculation(+, -, *, /)
     3.basic operation(=, >, <, ==, !=...)
     first version: 2014/02/03 
*/
/**********************************************************************************/

#ifndef BIGNUMBER_H
#define BIGNUMBER_H

#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>

#define MAX_VEC1 1000000000
#define MAX_VEC2 10000

using namespace std;

class BigNumber{
 public:
  //input
  BigNumber(){this->init("0");}//initial = 0
  template <class T> BigNumber(T);//can use any type that can be printed as number
  template <class T> BigNumber operator=(T);

  BigNumber abs();
  //TODO: use reference
  BigNumber operator+(BigNumber);
  BigNumber operator-(BigNumber);
  BigNumber operator-();//unary minus
  BigNumber operator*(const BigNumber&);
  BigNumber operator/(BigNumber&);
  bool operator>(BigNumber&);
  bool operator==(BigNumber&);
  bool operator>=(BigNumber& comp){return *this > comp || *this == comp;}
  bool operator!=(BigNumber& comp){return !(*this == comp);}
  bool operator<(BigNumber& comp){return !(*this >= comp);}
  bool isAbsSmaller(BigNumber& comp);
  bool isAbsGreater(BigNumber&);
  BigNumber operator+=(BigNumber& comp){return (*this) + comp;}
  BigNumber operator-=(BigNumber& comp){return (*this) - comp;}
  BigNumber operator*=(BigNumber& comp){return (*this) * comp;}
  BigNumber operator/=(BigNumber& comp){return (*this) / comp;}
  //output
  string getString();//get value as string 
  void print(){if(neg) putchar('-'); printf("%s", this->unsigned_string.c_str());}
  void print_line(){this->print(); puts("");}
  
 private:
  bool neg;
  string unsigned_string;
  int deg; //位數 //TODO: is it used?
    
  void reset_number(string);
  void init(string);
  BigNumber(vector<int>&, int, bool);

  vector<int> vec1; //used in +, -
  vector<int> vec2; //used in *
  void make_vector(vector<int>&, int);
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


