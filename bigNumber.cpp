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

string my_to_string(int v){
  //temps = std::to_string(vec[lo-1]); //so good!! but there are some bug by using g++
  char tempc[14];
  sprintf(tempc, "%d", v);
  return string(tempc);
}
void vector_to_string(vector<int> &vec, string &signed_string, int real, string append_zero, int ori_way, int i_end){
  for(int i = real-1; i >= i_end; i--){
    int temp = vec[i];
    if(temp == 0)
      signed_string.append(append_zero);
    else{
      //test
      //ref: http://stackoverflow.com/a/4133356
	char t[15];
	sprintf(t, "%0*d", ori_way, vec[i]);
	signed_string.append(string(t));
    }
  }
}
BigNumber::BigNumber(vector<int> &vec, int type, bool neg){//!!not ok//type 1 = +, - , 2 = * //12345678999 12345678900
  string signed_string;
  signed_string.clear();//!!?????!!
  if(neg)
    signed_string.insert(0, "-");//!!
  int lo = vec.size();
  int real = lo-1;
  while(vec[real] == 0 && real > 0)//prevent real==-1
    real--;
  signed_string.append(my_to_string(vec[real]));
  string append_zero;
  int way;
  int i_end;
  if(type == 1){
    append_zero = "000000000";//test: add additional zero -> yes, it need 9 zero
    way = 9;
    i_end = 0;
  } else if(type == 2){
    append_zero = "0000";
    way = 4;
    i_end = 2;
  } else {
    printf("type error!\n");
    return;
  }
  vector_to_string(vec, signed_string, real, append_zero, way, i_end);
  //printf("signed_string = %s\n", signed_string.c_str());
  this->init(signed_string);
}

void BigNumber::init(string s){
  if(s[0] == '-'){
    neg = true;
    s.erase(0, 1);
  } else {
    neg = false;
  }
  while(s[0] == '0' && s[1] != '\0'){
    s.erase(0,1);
  }
  this->unsigned_string = s;
  this->deg = s.size();
  this->make_vector1();
  this->make_vector2();
  return;
}
void BigNumber::make_vector1(){
  this->make_vector(this->vec1, 9);
}
void BigNumber::make_vector2(){
  this->make_vector(this->vec2, 4);
  this->vec2.insert(this->vec2.begin(), 0);//this zero is for ?? i don't know why... maybe look original code again?
}
void BigNumber::make_vector(vector<int>& vec, int maxdeg){
  //stringstream is much slower than atof, so no use stringstream  //ref: http://tinodidriksen.com/2011/05/28/cpp-convert-string-to-double-speed/
  vec.clear();
  string temp, unsigned_string = this->unsigned_string;
  int count = this->deg;
  do{
    count -= maxdeg;
    if(count > 0)
      temp.assign(unsigned_string, count, maxdeg);
    else
      temp.assign(unsigned_string, 0, count + maxdeg);//end of string
    vec.push_back(atof(temp.c_str()));
  }while(count > 0);//check
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
    for(int i = 0; i < this->deg; i++)
      if(this->unsigned_string[i] != comp.unsigned_string[i])
	return false;
  }
  return true;
}

string BigNumber::getString(){
  string signed_string = this->unsigned_string;
  if(neg)
    signed_string.insert(0, "-");
  return signed_string;
}

void BigNumber::reset_number(string s){
  this->init(s);
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
  } else { // 一般 (+) + (+) or (-) + (-)
    return this->add(added);
  }
}

BigNumber BigNumber::operator-(BigNumber minused){
  //TODO: refact to reverseSign()
  minused.neg = !minused.neg;//被減數變號，然後相加
  return (*this) + minused;
}


BigNumber BigNumber::operator*(BigNumber multiplier){
  int loa = this->vec2.size();
  int lob = multiplier.vec2.size();
  int lo = (loa>lob)?loa:lob;
  std::vector<int> ans;

  bool isneg;
  if(this->unsigned_string == "0" || multiplier.unsigned_string == "0")//ans = zero
    return BigNumber("0");
  else{
    isneg = check_multiply_divide_negative(this->neg, multiplier.neg);
          
    ans.assign(loa + lob, 0);//initialized to zero
    for(int i = 1; i < loa; i++)//start from 1
      for(int j = 1; j < lob; j++)
	ans[i+j] += (this->vec2[i] * multiplier.vec2[j]);
    //最後再進位即可！
    lo = ans.size();
    for(int i = 0; i < lo; i++)
      if(ans[i] >= MAX_VEC2){
	ans[i+1] += ans[i] / MAX_VEC2;
	ans[i] %= MAX_VEC2;
      }
  }
  return BigNumber(ans, 2, isneg);
}
inline bool BigNumber::check_multiply_divide_negative(bool a, bool b){
  return (a||b) && !(a&&b);
}

int new_guxuan(string tempt, vector<string>& mult){//binary?? // calculate the number of multiply
  //int start = 1, end = 9;
  //int mid = (start + end) / 2;
  //while(mid)
  for(int i = 9; i >= 1; i--){
    if(is_string_abs_geq(tempt, mult[i]))//if(tempt >= mult[i]), 有算degree??
      return i;
  }
  return -1;
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
  while(a[0] == '0'){
    a.erase(0, 1);
  }
}
void divide(string ts, string ds, string& ans){
  int ts_size = ts.size();
  int ds_size = ds.size();
  vector<string> mult(10);
  BigNumber ds_Big = BigNumber(ds);
  for(int i = 1; i < 10; i++){
    mult[i] = (BigNumber(i) * ds_Big).getString();
  }

  string tempt;
  const int MAX_ANS_DEGREE = ts_size - ds_size + 1;
          
  for(int i = 0 ; i < MAX_ANS_DEGREE; i++){
    if(ts.size() < ds_size)
      break;
    if(i == 0)
      tempt.assign(ts, 0, ds_size);//先取ds_size個數的數 //改成多加一位的方式
    else
      tempt.push_back(ts[tempt.size()]);

    if(is_string_abs_geq(tempt, ds)){//被除數較大
      int g = new_guxuan(tempt, mult);
      ans.push_back('0' + g);
               
      int tempt_size = tempt.size();
      string_minus(tempt, mult[g]);
      ts.erase(0, tempt_size);
      ts.insert(0, tempt);
    } else {//被除數較小
      if(ts.size() + tempt.size() == ds_size)//同長度，且被除數較小//TODO: know
	break;
      //加一位，再算
      ans.push_back('0');
    }
    // printf("nowans: %s, ts = %s\n", ans.c_str(), ts.c_str());
  }
  //補後方0
  int ans_size = ans.size();
  for(int i = 0; i < MAX_ANS_DEGREE - ans_size; i++){
    ans.push_back('0');
  }
  //去除前方0
  while(ans[0] == '0'){
    ans.erase(0, 1);
  }
}

BigNumber BigNumber::operator/(BigNumber devidend){//not sure
  int loa = this->vec2.size();
  int lob = devidend.vec2.size();
  int lo = (loa>lob)?loa:lob;

  if(devidend.unsigned_string == "0"){
    puts("Invalid operation: Divide by zero");
    return BigNumber("");//TODO:NAN
  } else if(this->unsigned_string == "0" || loa < lob){//除數 = 0？
    return BigNumber("0");
  } else if(loa == lob){//同長度
    for(int i = loa-1; i >= 0;i--){
      if(this->vec2[i] < devidend.vec2[i])
	return BigNumber("0");
      else if(this->vec2[i] > devidend.vec2[i])
	break;
    }
  }

  bool isneg = check_multiply_divide_negative(this->neg, devidend.neg);

  string ans;
  if(isneg)
    ans.insert(0, "-");
  divide(this->unsigned_string, devidend.unsigned_string, ans);
  return BigNumber(ans);
}
