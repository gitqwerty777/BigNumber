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
  }while(count > 0);
}

int compare_string_abs(string a, string b){
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

inline bool is_string_abs_geq(string a, string b){//greater or equal
  int cmp_value = compare_string_abs(a, b);
  if(cmp_value == 0)
    return true;
  else
    return (cmp_value > 0);
}
inline bool is_string_abs_greater(string a, string b){
  int cmp_value = compare_string_abs(a, b);
  if(cmp_value == 0)
    return false;
  else
    return (cmp_value > 0);
}
inline bool BigNumber::is_bignumber_abs_greater(BigNumber& b){
  return is_string_abs_greater(this->getString(), b.getString());
}
inline bool BigNumber::is_bignumber_abs_geq(BigNumber& b){
  return is_string_abs_geq(this->getString(), b.getString());
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
	return !this->is_bignumber_abs_geq(comp);
    } else{//+ +
      if(this->deg != comp.deg)
	return this->deg > comp.deg;
      else
	return this->is_bignumber_abs_greater(comp);
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

string BigNumber::getString(){
  string signed_string = this->unsigned_string;
  if(neg)
    signed_string.insert(0, "-");
  return signed_string;
}

// add and minus: doesn't consider positive and negative
BigNumber BigNumber::add(BigNumber& added){
  int loa = this->vec1.size();
  int lob = added.vec1.size();
  int lo = (loa>lob)?loa:lob;

  vector<int> ans;
  int flow = 0;
  if(loa >= lob)
    for(int i = 0; i < lo; i++){//use some pointer to replace
      if(i < lob)
	ans.push_back(this->vec1[i] + added.vec1[i] + flow);
      else
	ans.push_back(this->vec1[i] + flow);
               
      if(ans[i] >= MAX_VEC1){
	ans[i] -= MAX_VEC1;
	flow = 1;
      }
      else
	flow = 0;
    }
  else if(lob > loa)
    for(int i = 0; i < lo; i++){
      if(i < loa)
	ans.push_back(this->vec1[i] + added.vec1[i] + flow);
      else
	ans.push_back(added.vec1[i] + flow);
               
      if(ans[i] >= MAX_VEC1){
	ans[i] -= MAX_VEC1;
	flow = 1;
      }
      else
	flow = 0;
    }

  if(flow)//增加一位
    ans.push_back(1);
  return BigNumber(ans, 1, this->neg);
}
BigNumber BigNumber::minus(BigNumber& minused){//TODO:小減大problem
  std::vector<int> ans;
  int loa = this->vec1.size();
  int lob = minused.vec1.size();
  int lo = (loa > lob)?loa:lob;
  int flow = 0;
  //先比大小
  bool is_ans_pos = this->is_bignumber_abs_geq(minused);
  //大減小
  if(is_ans_pos)
    for(int i = 0; i < lo; i++){
      if(i < lob)//???
	ans.push_back(this->vec1[i] - minused.vec1[i] - flow);
      else
	ans.push_back(this->vec1[i] - flow);
      if(ans[i] < 0){
	ans[i] += MAX_VEC1;
	flow = 1;
      }
      else
	flow = 0;
    }
  else
    for(int i = 0; i < lo; i++){
      if(i < loa)//????
	ans.push_back(minused.vec1[i] - this->vec1[i] - flow);
      else
	ans.push_back(minused.vec1[i] - flow);
      if(ans[i] < 0){
	ans[i] += MAX_VEC1;
	flow = 1;
      }
      else
	flow = 0;
    }
  return BigNumber(ans, 1, !is_ans_pos);
}


BigNumber BigNumber::operator+(BigNumber added){//only consider sign
  if(this->neg && !added.neg){// -a + +b => b - a
    return added.minus(*this);//minus 不看 兩數之正負
  } else if(!this->neg && added.neg){//+a + -b => a - b
    return this->minus(added);
  } else { // (+) + (+) or (-) + (-)
    return this->add(added);
  }
}
BigNumber BigNumber::operator-(BigNumber minused){// a - b = a + (-b)
  minused.reverseSign();
  return (*this) + minused;
}
BigNumber BigNumber::operator-(){ //unary minus
  BigNumber tmp = BigNumber(*this);
  tmp.reverseSign();
  return tmp;
}
inline void BigNumber::reverseSign(){
  this->neg = !this->neg;
}

inline bool XOR(bool a, bool b){
  return (a||b) && !(a&&b);
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

int estimate(string tempt, vector<string>& mult){
  //binary search version
  int start = 9, end = 1;
  int mid = (start+end)/2;
  while(start > end){
    if(is_string_abs_geq(tempt, mult[mid])){
      if(mid+1 <= 9 && is_string_abs_geq(tempt, mult[mid+1]))
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
    if(is_string_abs_geq(tempt, mult[i]))
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
void divide(string ts, string ds, string& ans){
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

    if(is_string_abs_geq(tempt, ds)){
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

BigNumber BigNumber::operator/(BigNumber& divisor){//not sure
  int loa = this->vec2.size();
  int lob = divisor.vec2.size();
  int lo = (loa>lob)?loa:lob;

  //special case
  if(divisor.unsigned_string == "0"){
    puts("Invalid operation: Divide by zero");
    return BigNumber("");//TODO:NAN
  } else if(this->absSmaller(divisor) || this->unsigned_string == "0"){
    return BigNumber("0");
  }

  string ans;
  bool isneg = XOR(this->neg, divisor.neg);

  if(isneg)
    ans.insert(0, "-");
  divide(this->unsigned_string, divisor.unsigned_string, ans);
  return BigNumber(ans);
}
