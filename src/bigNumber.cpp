#include "bigNumber.h"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <string>
#include <string.h>
#include <stdio.h>
#define MAX_VEC1 1000000000
#define MAX_VEC2 10000
using namespace std;

string myToString(int v);
void VectorToString(vector<int> &vec, string &signed_string, int realstart, string append_zero, int ori_way, int i_end);
inline bool XOR(bool a, bool b){
  return (a||b) && !(a&&b);
}

BigNumber BigNumber::operator+(BigNumber added){//only consider sign
  if(this->neg && !added.neg){// -a + +b => b - a
    return added.minus(*this);
  } else if(!this->neg && added.neg){//+a + -b => a - b
    return this->minus(added);
  } else { // (+) + (+) or (-) + (-)
    return this->add(added);
  }
}
BigNumber BigNumber::operator-(BigNumber minused){//only consider sign
  // a - b = a + (-b)
  minused.reverseSign();
  return (*this) + minused;
}
//add and minus don't consider positive and negative
BigNumber BigNumber::add(BigNumber& added){
  //long and short
  vector<int> vecl = this->vec1;
  vector<int> vecs = added.vec1;
  if(vecl.size() < vecs.size()){//do not need to compare number 
    vector<int> tmp = vecl;
    vecl = vecs;
    vecs = tmp;
  }
  int loa = vecl.size();
  int lob = vecs.size();
  
  vector<int> ans;
  int carry = 0;
  for(int i = 0; i < loa; i++){
    if(i < lob)
      ans.push_back(vecl[i] + vecs[i] + carry);
    else
      ans.push_back(vecl[i] + carry);
               
    if(ans[i] >= MAX_VEC1){
      ans[i] -= MAX_VEC1;
      carry = 1;
    }
    else
      carry = 0;
  }

  if(carry)
    ans.push_back(1);
  return BigNumber(ans, 1, this->neg);
}
BigNumber BigNumber::minus(BigNumber& minused){//TODO:小減大problem
  //long and short
  vector<int> vecl = this->vec1;
  vector<int> vecs = minused.vec1;
  vector<int> ans;
  bool isneg = false;
  if(this->isAbsSmaller(minused)){//only minus need to compare number
    vector<int> tmp = vecl;
    vecl = vecs;
    vecs = tmp;
    isneg = true;
  }
  int loa = vecl.size();
  int lob = vecs.size();
  int carry = 0;

  for(int i = 0; i < loa; i++){
    if(i < lob)
      ans.push_back(vecl[i] - vecs[i] - carry);
    else
      ans.push_back(vecl[i] - carry);
    if(ans[i] < 0){
      ans[i] += MAX_VEC1;
      carry = 1;
    }
    else
      carry = 0;
  }
  return BigNumber(ans, 1, isneg);
}
BigNumber BigNumber::operator-(){ //unary minus
  BigNumber tmp = BigNumber(*this);
  tmp.reverseSign();
  return tmp;
}
inline void BigNumber::reverseSign(){
  this->neg = !this->neg;
}

BigNumber BigNumber::operator*(BigNumber multiplier){
  if(this->unsigned_string == "0" || multiplier.unsigned_string == "0")//ans = zero
    return BigNumber("0");

  int loa = this->vec2.size();
  int lob = multiplier.vec2.size();
  int lo = (loa>lob)?loa:lob;

  bool isneg = XOR(this->neg, multiplier.neg);

  std::vector<int> ans;
  ans.assign(loa + lob, 0);//initialized to zero
  //TODO: find way to make index start from 0
  for(int i = 1; i < loa; i++)//should start from 1
    for(int j = 1; j < lob; j++)
      ans[i+j] += (this->vec2[i] * multiplier.vec2[j]);
  //carry
  lo = ans.size();
  for(int i = 0; i < lo; i++)
    if(ans[i] >= MAX_VEC2){
      ans[i+1] += ans[i] / MAX_VEC2;
      ans[i] %= MAX_VEC2;
    }
  return BigNumber(ans, 2, isneg);
}

BigNumber BigNumber::operator/(BigNumber& divisor){//not sure
  int loa = this->vec2.size();
  int lob = divisor.vec2.size();
  int lo = (loa>lob)?loa:lob;

  //special case
  if(divisor.unsigned_string == "0"){
    puts("Invalid operation: Divide by zero");
    return BigNumber("");//TODO:NAN
  } else if(this->isAbsSmaller(divisor) || this->unsigned_string == "0"){
    return BigNumber("0");
  }

  string ans;
  bool isneg = XOR(this->neg, divisor.neg);

  if(isneg)
    ans.insert(0, "-");
  divide(this->unsigned_string, divisor.unsigned_string, ans);
  return BigNumber(ans);
}
int BigNumber::estimate(string tempt, vector<string>& mult){
  //binary search version
  int start = 9, end = 1;
  int mid = (start+end)/2;
  while(start > end){
    if(isStringAbsGeq(tempt, mult[mid])){
      if(mid+1 <= 9 && isStringAbsGeq(tempt, mult[mid+1]))
	end = mid+1;
      else
	return mid;
    }
    else
      start = mid-1;
    mid = (start+end)/2;
  }
  return mid;
  /*
  //linear search version
  for(int i = 9; i >= 1; i--)
    if(isStringAbsGeq(tempt, mult[i]))
      return i;
  return -1;
  */
}
void string_minus(string& a, string b){
  int a_size = a.size()-1;//index
  int b_size = b.size()-1;//index(-1)
  for(int i = 0; i <= b_size; i++){
    a[a_size-i] -= b[b_size-i] - '0';
    if(a[a_size-i] < '0'){
      a[a_size-i] += 10;
      a[a_size-i-1] -= 1;
    }
  }
  while(a[0] == '0')
    a.erase(0, 1);
}
void BigNumber::divide(string ts, string ds, string& ans){
  vector<string> mult(10);
  BigNumber ds_Big = BigNumber(ds);
  for(int i = 1; i < 10; i++)
    mult[i] = (BigNumber(i) * ds_Big).getString();

  int tsize = ts.size();
  int dsize = ds.size();
  const int MAXDEGREE = tsize - dsize + 1;

  string tempt;
  for(int i = 0 ; i < MAXDEGREE; i++){
    if(ts.size() < dsize)//ts.size() will change
      break;
    if(i == 0)
      tempt.assign(ts, 0, dsize);//add dsize digit at first time
    else
      tempt.push_back(ts[tempt.size()]);//add one digit each iteration

    if(isStringAbsGeq(tempt, ds)){
      int g = estimate(tempt, mult);
      ans.push_back('0' + g);
      ts.erase(0, tempt.size());
      string_minus(tempt, mult[g]);               
      ts.insert(0, tempt);
    } else { //will get 0, add more digit
      ans.push_back('0');
    }
  }

  int ans_size = ans.size();
  for(int i = 0; i < MAXDEGREE - ans_size; i++)//can't be divided at last, add 0
    ans.push_back('0');
  while(ans[0] == '0')//remove previous 0
    ans.erase(0, 1);
}

BigNumber BigNumber::abs(){
  if(this->neg){
    BigNumber tmp = BigNumber(*this);
    tmp.neg = false;
    return tmp;
  } else
    return *this;
}
string BigNumber::getString(){
  string signed_string = this->unsigned_string;
  if(neg)
    signed_string.insert(0, "-");
  return signed_string;
}

bool BigNumber::operator>(BigNumber &comp){
  if(!this->neg && comp.neg){//+  > -
    return true;
  }else if(this->neg && !comp.neg){// - < +
    return false;
  } else{
    if(this->neg){//- -
      if(this->deg != comp.deg)
	return this->deg < comp.deg;
      else
	return !this->isAbsGeq(comp);
    } else{//+ +
      if(this->deg != comp.deg)
	return this->deg > comp.deg;
      else
	return this->isAbsGreater(comp);
    }
  }
}
bool BigNumber::operator==(BigNumber &comp){
  if(this->neg != comp.neg || this->deg != comp.deg){
    return false;  
  } else {
    return (this->unsigned_string == comp.unsigned_string);
  }
}
inline bool BigNumber::isAbsGreater(BigNumber& b){
  return isStringAbsGreater(this->getString(), b.getString());
}
inline bool BigNumber::isAbsGeq(BigNumber& b){
  return isStringAbsGeq(this->getString(), b.getString());
}
inline bool BigNumber::isAbsSmaller(BigNumber& comp){
  return !this->isAbsGeq(comp);
}
inline bool BigNumber::isStringAbsGeq(string a, string b){//greater or equal
  int cmp_value = strcmp_abs(a, b);
  if(cmp_value == 0)
    return true;
  else
    return (cmp_value > 0);
}
inline bool BigNumber::isStringAbsGreater(string a, string b){
  int cmp_value = strcmp_abs(a, b);
  if(cmp_value == 0)
    return false;
  else
    return (cmp_value > 0);
}
int BigNumber::strcmp_abs(string a, string b){
  while(a[0] == '0' || a[0] == '-')
    a.erase(0, 1);
  while(b[0] == '0' || b[0] == '-')
    b.erase(0, 1);
  if(a.size() != b.size()){
    return a.size() - b.size();
  } else {
    for(int i = 0; i < a.size(); i++)
      if(a[i] != b[i])
	return a[i] - b[i];
  }
  return 0;
}

BigNumber::BigNumber(vector<int> &vec, int type, bool neg){//type 1 = add/minus,2 = multiply //12345678999 12345678900
  string signed_string;
  if(neg)
    signed_string.insert(0, "-");
  int lo = vec.size();
  int realstart = lo-1;
  while(vec[realstart] == 0 && realstart > 0)
    realstart--;
  signed_string.append(myToString(vec[realstart]));
  string append_zero;  int way;  int i_end;
  if(type == 1){
    append_zero = "000000000";
    way = 9;
    i_end = 0;
  } else if(type == 2){
    append_zero = "0000";
    way = 4;
    i_end = 2;// two zero that append at make_vector2()
  } else {
    fprintf(stderr, "type error!\n");
    exit(1);
    return;
  }
  VectorToString(vec, signed_string, realstart, append_zero, way, i_end);
  this->init(signed_string);
}
string myToString(int v){
  //temps = std::to_string(v); //so good!! but there are some bug when using g++
  char tempc[14];
  sprintf(tempc, "%d", v);
  return string(tempc);
}
void VectorToString(vector<int> &vec, string &signed_string, int realstart, string append_zero, int ori_way, int i_end){
  for(int i = realstart-1; i >= i_end; i--){
    int temp = vec[i];
    if(temp == 0)
      signed_string.append(append_zero);
    else{
	char t[15];
	sprintf(t, "%0*d", ori_way, vec[i]); //ref: http://stackoverflow.com/a/4133356
	signed_string.append(string(t));
    }
  }
}
void BigNumber::reset_number(string s){
  this->init(s);
}
void BigNumber::init(string s){
  if(s[0] == '-'){
    neg = true;
    s.erase(0, 1);
  } else {
    neg = false;
  }
  while(s[0] == '0')
    s.erase(0,1);
  if(s == "")
    s = string("0");
  this->unsigned_string = s;
  this->deg = s.size();
  this->make_vector1();
  this->make_vector2();
  return;
}
void BigNumber::make_vector1(){//make vector for add/minus
  this->make_vector(this->vec1, 9);
}
void BigNumber::make_vector2(){//make vector for multiply
  this->make_vector(this->vec2, 4);
  this->vec2.insert(this->vec2.begin(), 0);//multiply should start from 1
}
void BigNumber::make_vector(vector<int>& vec, int maxdeg){
  vec.clear();
  string temp, unsigned_string = this->unsigned_string;
  int count = this->deg;
  //convert string into ints, by reverse order
  //maxdeg is largest degree that every int has
  // e.g. , makevector(, 4) = 2147483647 -> 3647, 4748, 21
  do{
    count -= maxdeg;
    if(count > 0)
      temp.assign(unsigned_string, count, maxdeg);
    else
      temp.assign(unsigned_string, 0, count + maxdeg);//end of string
    vec.push_back(atof(temp.c_str()));
  }while(count > 0);}
