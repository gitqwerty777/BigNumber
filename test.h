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
     Author: HCL start from 2014/02/03 to 2014/05/27
*/
/**********************************************************************************/
#include <iostream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <string>
#include <string.h>
#define VEC1N 1000000000
using namespace std;

/*
*    NOW Progress:
*    1. Deal with negative number => +, - ok
*    3. >_< ?
*    4. statement
*    5. big_to_s, s_to_big??
*    6. 效能, memory
*    7.http://stackoverflow.com/a/12975602/2678970
*/

class BigNumber{
     public:
          BigNumber();
          template <class T> BigNumber(T);
          BigNumber(vector<int>&, int, bool);
          BigNumber operator+(BigNumber);//const??
          BigNumber operator-(BigNumber);
          BigNumber operator*(BigNumber);
          BigNumber operator/(BigNumber);
          bool operator>(BigNumber&);
          bool operator>=(BigNumber&);
          bool operator==(BigNumber&);
          // todo +=, ... 
          string get_bignumber_string();//get string type of Bignumber
          void print_number();
          void print_number_oneline();//print in a line
     private: 
          bool is_bignumber_abs_greater(BigNumber&);
          bool is_bignumber_abs_geq(BigNumber&);
          void reset_number(string);
          void init(string);
          void make_vector(vector<int>&, int);
          void make_vector1();
          void make_vector2();
          BigNumber minus(BigNumber&);
          BigNumber add(BigNumber&);
          bool neg; // negative or not
          string abs_string;
          int deg; //位數
          vector<int> vec1; //used in +, -
          vector<int> vec2; //used in *
};
typedef class BigNumber intxx;


bool is_string_abs_geq(string a, string b){ // if a >= b, return true, if a < b, return false
     while(a[0] == '0')
          a.erase(0, 1);
     while(b[0] == '0')
          b.erase(0, 1);
     if(a.size() != b.size()){
          return a.size() > b.size();
     } else {
          for(int i = 0; i < a.size(); i++){
               if(a[i] != b[i]){
                    return a[i] > b[i];
               }
          }
     }
     return true;
}
bool is_string_abs_greater(string a, string b){ // if a >= b, return true, if a < b, return false
     while(a[0] == '0')
          a.erase(0, 1);
     while(b[0] == '0')
          b.erase(0, 1);
     if(a.size() != b.size()){
          return a.size() > b.size();
     } else {
          for(int i = 0; i < a.size(); i++){
               if(a[i] != b[i]){
                    return a[i] > b[i];
               }
          }
     }
     return false;
}

bool BigNumber::is_bignumber_abs_greater(BigNumber& b){//only used when string is in the same degree
     return is_string_abs_greater(this->get_bignumber_string(), b.get_bignumber_string());
}
bool BigNumber::is_bignumber_abs_geq(BigNumber& b){//greater or equal >= 
     return is_string_abs_geq(this->get_bignumber_string(), b.get_bignumber_string());
}

bool BigNumber::operator>(BigNumber &comp){
     if(!this->neg && comp.neg){
          return true;
     }else if(this->neg && !comp.neg){   
          return false;
     } else{
          if(this->neg){//all negative
               if(this->deg != comp.deg){
                    return this->deg < comp.deg;
               } else{
                    return !this->is_bignumber_abs_geq(comp);
               }
          } else{//all positive
               if(this->deg != comp.deg){
                    return this->deg > comp.deg;
               } else{
                    return this->is_bignumber_abs_greater(comp);
               }
          }
     }
}

bool BigNumber::operator==(BigNumber &comp){
     if(this->neg != comp.neg || this->deg != comp.deg){
          return false;  
     } else {
          for(int i = 0; i < this->deg; i++)
               if(this->abs_string[i] != comp.abs_string[i])
                    return false;
     }
     return true;
}

bool BigNumber::operator>=(BigNumber &comp){
     if(*this > comp || *this == comp){
          return true;
     } else {
          return false;
     }
}

string BigNumber::get_bignumber_string(){
     string full_string = this->abs_string;
     if(neg)
          full_string.insert(0, "-");
     return full_string;
}

void BigNumber::print_number(){
     if(neg)
          putchar('-');
     printf("%s", this->abs_string.c_str());
}
void BigNumber::print_number_oneline(){
     if(neg)
          putchar('-');
     puts(this->abs_string.c_str());
}

void BigNumber::reset_number(string s){
     this->init(s);
}

BigNumber::BigNumber(){
     this->init("");
}

template <class T>
BigNumber::BigNumber(T template_init){
     string s;
     stringstream ss; 
     ss<<template_init;
     ss>>s;
     this->init(s);
}

template <>
BigNumber::BigNumber<string>(string s){
     this->init(s);
}


void BigNumber::init(string s){
     if(s[0] == '-'){
          neg = true;
          s.erase(0, 1);
     } else {
          neg = false;
     }
     this->abs_string = s;
     this->deg = s.size();
     this->make_vector1();
     this->make_vector2();
     return;
}

void BigNumber::make_vector(vector<int>& vec, int maxdeg){
     //stringstream is much slower than atof
     //so no use stringstream
     //ref: http://tinodidriksen.com/2011/05/28/cpp-convert-string-to-double-speed/
     vec.clear();
     string temp, abs_string = this->abs_string;
     int count = this->deg;
     do{
          count -= maxdeg;
          if(count > 0)
               temp.assign(abs_string, count, maxdeg);
         else
               temp.assign(abs_string, 0, count + maxdeg);//end of string
          vec.push_back(atof(temp.c_str()));
     }while(count > 0);//check
}

void BigNumber::make_vector1(){
     this->make_vector(this->vec1, 9);
}
void BigNumber::make_vector2(){
     this->make_vector(this->vec2, 4);
     this->vec2.insert(this->vec2.begin(), 0);//this zero is for ?? i don't know why... maybe look original code again?
}

BigNumber::BigNumber(vector<int> &vec, int type, bool neg){//!!not ok//type 1 = +, - , 2 = * //12345678999 - 12345678900
     int i;
     string s, temps;
     char tempc[14];
     if(neg)
          s.append("-");
     int lo = vec.size();
     if(type == 1){
          sprintf(tempc, "%d", vec[lo-1]);
          //temps = std::to_string(vec[lo-1]); //so good!! but it has some bug in g++
          s.append(string(tempc));
          for(int i = lo-2; i >= 0; i--){
               int way = 9; int temp = vec[i];
               if(vec[i] == 0)
                    s.append("00000000");
               else{
                    while(temp != 0){
                         temp /= 10;
                         way--;
                    }
                    while(way-- != 0)
                         s.append("0");
               }
               sprintf(tempc, "%d", vec[i]);
               //temps = std::to_string(vec[lo-1]); //so good!! but it has some bug in g++
               s.append(string(tempc));
          }
     } else if(type == 2){
          int way, tempa, real;
          real = lo-1;
          while(vec[real] == 0)
               real--;
          sprintf(tempc, "%d", vec[real]);
          //temps = std::to_string(vec[lo-1]); //so good!! but it has some bug in g++
          s.append(string(tempc));
          for(i = real-1; i >= 2; i--){
               way = 4; tempa = vec[i];
               if(vec[i] == 0)
                    s.append("000");
               else{
                    while(tempa != 0){
                         tempa /= 10;
                         way--;
                    }
                    while(way-- != 0)
                         s.append("0");
               }
               sprintf(tempc, "%d", vec[i]);
               //temps = std::to_string(vec[lo-1]); //so good!! but it has some bug in g++
               s.append(string(tempc));
          }
     } else if(type == 3){
          int lo = vec.size();
          for(int i = 0; i < lo ; i++){
              sprintf(tempc, "%d", vec[i]);
               //temps = std::to_string(vec[lo-1]); //so good!! but it has some bug in g++
               s.append(string(tempc));
          }
     } else {
          printf("type error!\n");
     }
     this->init(s);
}

void make_bignumber_by_vec1(bool neg, vector<int>& vec){//todo: not ok
     string s;
     char tempc[14];
     int lo = vec.size();
     
     if(neg)
          s.append("-");
     //temps = std::to_string(vec[lo-1]); //so good!! but it has some bug in g++
     sprintf(tempc, "%d", vec[lo-1]);
     s.append(string(tempc)); //first one, no need to add forward zero
     for(int i = lo-2; i >= 0; i--){
          int way = 9; int temp = vec[i];
          if(vec[i] == 0)
               s.append("00000000");
          else{
               while(temp != 0){
                    temp /= 10;
                    way--;
               }
               while(way--)
                    s.append("0");
          }
          //temps = std::to_string(vec[lo-1]); //so good!! but it has some bug in g++
          sprintf(tempc, "%d", vec[i]);
          s.append(string(tempc));
     }
}

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
               
               if(ans[i] >= VEC1N){
                    ans[i] -= VEC1N;
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
               
               if(ans[i] >= VEC1N){
                      ans[i] -= VEC1N;
                      flow = 1;
               }
               else
                    flow = 0;
          }

     if(flow)//增加一位
          ans.push_back(1);
     return BigNumber(ans, 1, this->neg);
}

BigNumber BigNumber::minus(BigNumber& minused){//todo 小減大problem
     //先比大小
     bool is_ans_neg = !this->is_bignumber_abs_greater(minused);
     //大減小

     std::vector<int> ans;
     int loa = this->vec1.size();
     int lob = minused.vec1.size();
     int lo = (loa > lob)?loa:lob;
     int flow = 0;

     if(is_ans_neg)//abstract
          for(int i = 0; i < lo; i++){
               if(i < lob)//???
                    ans.push_back(this->vec1[i] - minused.vec1[i] - flow);
               else
                    ans.push_back(this->vec1[i] - flow);
               if(ans[i] < 0){
                    ans[i] += VEC1N;
                    flow = 1;
               }
               else
                    flow = 0;
          }
     else
          for(int i = 0; i < lo; i++){
               if(i < lob)//????
                    ans.push_back(minused.vec1[i] - this->vec1[i] - flow);
               else
                    ans.push_back(minused.vec1[i] - flow);
               if(ans[i] < 0){
                    ans[i] += VEC1N;
                    flow = 1;
               }
               else
                    flow = 0;
          }

     return BigNumber(ans, 1, !is_ans_neg);
}

BigNumber BigNumber::operator+(BigNumber added){//int + big??
     if(this->neg && !added.neg){// -a + +b => b - a
          return (added).minus(*this);//minus 不看 兩數之正負
     } else if(!this->neg && added.neg){//+a + -b => a - b
          return this->minus(added);
     } else { // 一般 (+) + (+) or (-) + (-)
          return this->add(added);
     }
}

BigNumber BigNumber::operator-(BigNumber minused){/* use stringstream to output the result to this->ori, instead of print*/
     minused.neg = !minused.neg;//被減數變號，然後相加
     BigNumber ans = (*this) + minused;
     return ans;
}

BigNumber BigNumber::operator*(BigNumber multiplied){
     int loa = this->vec2.size();
     int lob = multiplied.vec2.size();
     int lo = (loa>lob)?loa:lob;
     std::vector<int> ans;

     bool isneg;
     if(this->abs_string == "0" || multiplied.abs_string == "0")//ans = zero
          return BigNumber("0");
     else{
          if(this->neg || multiplied.neg){
               if(this->neg && multiplied.neg)
                    isneg = false;
               else
                    isneg = true;
          } else{
               isneg = false;
          }

          ans.assign(loa + lob, 0);//initialized to zero
          for(int i = 1; i < loa; i++)//from 1
               for(int j = 1; j < lob; j++){
                    ans[i + j] += (this->vec2[i] * multiplied.vec2[j]);
                    
                    if(ans[i + j] >= 10000){
                         ans[i + j + 1] += ans[i + j] / 10000;
                         ans[i + j] %= 10000;
                    }
               }
          //最後再進位即可！
          lo = ans.size();
          for(int i = 0; i < lo; i++)
               if(ans[i] >= 10000){
                    ans[i+1] += ans[i] / 10000;
                    ans[i] %= 10000;
               }
     }
     return BigNumber(ans, 2, isneg);
}

int new_guxuan(string tempt, vector<string>& mult){//binary??
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
     printf("%s - %s =", a.c_str(), b.c_str());
     int a_size = a.size()-1;//index
     int b_size = b.size()-1;//index(-1)
     for(int i = 0; i <= b_size; i++){
          a[a_size - i] -= b[b_size - i] - '0';
          if(a[a_size - i] < '0'){
               a[a_size - i] += 10;
               a[a_size - i - 1] -= 1;
          }
     }
     while(a[0] == '0'){
          a.erase(0, 1);
     }
     printf("%s\n", a.c_str());
}

void divide(string ts, string ds, string& ans){
     int ts_size = ts.size();
     int ds_size = ds.size();
     BigNumber ts_B = BigNumber(ts);

     vector<string> mult(10);
     BigNumber ds_Big = BigNumber(ds);
     for(int i = 1; i < 10; i++){
          mult[i] = (BigNumber(i) * ds_Big).get_bignumber_string();
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
          //printf("tempt = %s\n", tempt.c_str());
          if(is_string_abs_geq(tempt, ds)){//被除數較大
               int g = new_guxuan(tempt, mult);
               ans.push_back('0' + g);
               
               int tempt_size = tempt.size();
               string_minus(tempt, mult[g]);
               ts.erase(0, tempt_size);
               ts.insert(0, tempt);
          } else {//被除數較小
               if(ts.size() + tempt.size() == ds_size)//同長度，且被除數較小
                    break;
               //加一位，再算
               ans.push_back('0');
          }
         // printf("nowans: %s, ts = %s\n", ans.c_str(), ts.c_str());
     }
     //補齊0？
     int ans_size = ans.size();
     for(int i = 0; i < MAX_ANS_DEGREE - ans_size; i++){
          ans.push_back('0');
     }
     //去除前方的0
     while(ans[0] == '0'){
          ans.erase(0, 1);
     }
}

bool check_multiply_divide_negative(bool a, bool b){
     if(a || b){
          if(a && b)
               return false;
          else
               return true;
     } else {
          return false;
     }       
}

BigNumber BigNumber::operator/(BigNumber devidend){//not sure
     int loa = this->vec2.size();
     int lob = devidend.vec2.size();
     int lo = (loa>lob)?loa:lob;

     if(devidend.abs_string == "0"){
          puts("Invalid operation: Divide by zero");
          return BigNumber("");//todo: what should be put in?
     } else if(this->abs_string == "0" || loa < lob){//除數 = 0？
          return BigNumber("0");
     } else if(loa == lob){//同長度
          for(int i = loa-1; i >= 0;i--){
               if(this->vec2[i] < devidend.vec2[i])
                    return BigNumber("0");
               else if(this->vec2[i] > devidend.vec2[i])
                    break;
          }
     }
    
     bool isneg;

     if(this->neg || devidend.neg){
          if(this->neg && devidend.neg)
               isneg = false;
          else
               isneg = true;
     } else {
          isneg = false;
     }

     string ans;
     divide(this->abs_string, devidend.abs_string, ans);
     if(isneg)
          ans.insert(0, "-");
     return BigNumber(ans);
}
