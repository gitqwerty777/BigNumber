/**********************************************************************************/
/*   Usage:
     Some useful functions to deal with big integer number(the number which can't store by long long).
     1.transform string into big number structure, or transform big number structure to string
     2.basic calculation of big number.(+, -, *, /)
     3.print big numbers by string.
     Need to Improve:
     1.compatible with complex number
     2.additional mathmatical calculation %, ^, ()
     3.execution speed
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
 *    Known Bug:
 *    0 0 // ok -> by Bignumber() -> prevent real==0
 *    add NaN
 *    append -> insert
 *    前導0(test)
 *    NOW Progress:
 *    3. use constant values
 *    6. 效能, memory
 *            OPERATOR
 */

class BigNumber{
 public:
  BigNumber(){
    this->init("0");
  }
  template <class T> BigNumber(T);
  BigNumber(vector<int>&, int, bool);
  
  BigNumber operator+(BigNumber);//const??
  BigNumber operator-(BigNumber);
  BigNumber operator*(BigNumber);
  BigNumber operator/(BigNumber);

  template <class T> void operator=(T);// assign any value into BigNumber structure
  bool operator>(BigNumber&);
  bool operator==(BigNumber&);
  bool operator>=(BigNumber& comp){
    return *this > comp || *this == comp;}
  bool operator!=(BigNumber& comp){
    return !(*this == comp);}
  bool operator<(BigNumber& comp){
    return !(*this >= comp);}
  // TODO: +=, -=, *=, /=
  string getString();//get Bignumber in string type
  void print(){
    if(neg) putchar('-');
    printf("%s", this->unsigned_string.c_str());
  }
  void print_line(){
    this->print();
    puts("");
  }
  
 private:

  bool neg; // negative or not
  string unsigned_string;
  int deg; //位數

  void reset_number(string);
  void init(string);
  
  vector<int> vec1; //used in +, -
  vector<int> vec2; //used in *
  void make_vector(vector<int>&, int);
  void make_vector1();
  void make_vector2();
  
  BigNumber minus(BigNumber&);
  BigNumber add(BigNumber&);
  bool is_bignumber_abs_greater(BigNumber&);
  bool is_bignumber_abs_geq(BigNumber&);
  bool check_multiply_divide_negative(bool, bool);
};

//Template classes need to have the method definitions inside the header file. <http://stackoverflow.com/questions/9191210/templates-and-separate-compilation>
#include "bigNumber.hpp"
  
#endif


