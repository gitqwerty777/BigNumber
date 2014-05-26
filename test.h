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
          4.input with calculation form, output the answer
     Language: CPP
     Author: HCL start from 2014/02/03 to 2014/05/26
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
*/

class BigNumber{
     public:
          BigNumber();
          BigNumber(string);
          BigNumber(int);
          BigNumber(long long);
          BigNumber(vector<int>&, int, bool);
          BigNumber operator+(BigNumber);//const??
          BigNumber operator-(BigNumber);
          BigNumber operator*(BigNumber);
          BigNumber operator/(BigNumber);
          bool operator>(BigNumber&);
          bool operator>=(BigNumber&);
          string get_string_number();//get string type of Bignumber
          void set_number(string);
          void print_number();//print in a line
     private: 
          void init(string);
          void make_vector(vector<int>&, int);
          void make_vector1();
          void make_vector2();
          string num_str; //original string type
          bool neg; // negative or not
          int deg; //位數
          vector<int> vec1; //used in +, - //use string or int???
          vector<int> vec2; //used in *, /
          int getvec1(int);
          int getvec2(int);
          BigNumber minus(BigNumber&);
          BigNumber add(BigNumber&);
          bool absgeq(BigNumber&, BigNumber&);//greater or equal
          bool compare_string(BigNumber&, BigNumber&);
          bool compare_string_eq(BigNumber&, BigNumber&);
};
typedef class BigNumber intxx;

bool BigNumber::compare_string_eq(BigNumber& a, BigNumber& b){
     return a.get_string_number() >= b.get_string_number();
}
bool BigNumber::compare_string(BigNumber& a, BigNumber& b){
     return a.get_string_number() > b.get_string_number();
}

int BigNumber::getvec1(int i){
     return this->vec1[i];
}
int BigNumber::getvec2(int i){
     return this->vec2[i];
}

void BigNumber::print_number(){
     if(neg)
          putchar('-');
     puts(this->num_str.c_str());
}
string BigNumber::get_string_number(){
     return this->num_str;
}
void BigNumber::set_number(string s){
     this->init(s);
}

void BigNumber::init(string s){
     if(s[0] == '-'){
          neg = true;
          s.erase(0, 1);
     } else {
          neg = false;
     }
     this->num_str = s;
     this->deg = s.size();
     this->make_vector1();
     this->make_vector2();
     return;
}
BigNumber::BigNumber(){
     this->init("");
}
BigNumber::BigNumber(string s){
     this->init(s);
}
BigNumber::BigNumber(int l){
     char temp[15];
     sprintf(temp, "%d", l);
     this->init(temp);
}
BigNumber::BigNumber(long long l){
     char temp[100];
     sprintf(temp, "%lld", l);
     this->init(temp);
}
//!!not ok
BigNumber::BigNumber(vector<int> &vec, int type, bool neg){//type 1 = vec1, 2 = *, 3 = / 
     int i;
     string s, temps;
     char* tempc = (char*)malloc(sizeof(char) * 14);
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

void BigNumber::make_vector(vector<int>& vec, int maxdeg){//use stringstream instead of atof
     vec.clear();
     string temp, num_str = this->num_str;
     int i = 0, count = this->deg;
     do{
          count -= maxdeg;
          if(count > 0)
               temp.assign(num_str, count, maxdeg);
         else
               temp.assign(num_str, 0, count + maxdeg);//end of string
          vec.push_back(atof(temp.c_str()));
          i++;
     }while(count > 0);//check
}
void BigNumber::make_vector1(){
     this->make_vector(this->vec1, 9);
}
void BigNumber::make_vector2(){
     this->make_vector(this->vec2, 4);
     this->vec2.insert(this->vec2.begin(), 0);//i don;t know why... maybe look original code again?
}

bool BigNumber::absgeq(BigNumber& a, BigNumber& b){
     if(a.deg > b.deg){
          return true;
     } else if(a.deg < b.deg){
          return false;
     } else {
          for(int i = 0; i < a.deg; i++){
               if(a.num_str[i] > b.num_str[i])
                    return true;
               else if(a.num_str[i] < b.num_str[i])
                    return false;
          }
     }
     return true;//if the same , return true
}

BigNumber BigNumber::minus(BigNumber& minused){
     //先比大小
     bool tominus_bigger;
     if(absgeq(*this, minused)){
          tominus_bigger = true;
     } else {
          tominus_bigger = false;
     }
     //大減小

     std::vector<int> ans;
     int loa = this->vec1.size();
     int lob = minused.vec1.size();
     int lo = (loa > lob)?loa:lob;
     int flow = 0;

     if(tominus_bigger)//abstract
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

     return BigNumber(ans, 1, !tominus_bigger);
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

bool BigNumber::operator>(BigNumber &comp){//!!not ok//不看正負
     if(!this->neg && comp.neg){
          return true;
     }else if(this->neg && !comp.neg){   
          return false;
     } else{
          if(this->neg){//all negative
               if(this->deg != comp.deg){
                    return this->deg < comp.deg;
               } else{
                    return !compare_string_eq(*this, comp);
               }
          } else{//all positive
               if(this->deg != comp.deg){
                    return this->deg > comp.deg;
               } else{
                    return compare_string(*this, comp);
               }
          }
     }
}

bool BigNumber::operator>=(BigNumber &comp){//!!not ok//不看正負
     if(!this->neg && comp.neg){
          return true;
     }else if(this->neg && !comp.neg){   
          return false;
     } else{
          if(this->neg){//all negative
               if(this->deg != comp.deg){
                    return this->deg < comp.deg;
               } else{
                    return !compare_string(*this, comp);
               }
          } else{//all positive
               if(this->deg != comp.deg){
                    return this->deg > comp.deg;
               } else{
                    return compare_string_eq(*this, comp);
               }
          }
     }
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
     minused.neg = !minused.neg;//改回原狀
     return ans;
}

BigNumber BigNumber::operator*(BigNumber multiplied){
     int loa = this->vec2.size();
     int lob = multiplied.vec2.size();
     int lo = (loa>lob)?loa:lob;
     std::vector<int> ans;

     bool isneg;
     if(this->num_str == "0" || multiplied.num_str == "0")//!!iszero
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

          ans.assign(loa + lob, 0);//設為00000
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

int new_guxuan(string tempt, vector<class BigNumber>& mult){//binary??
     //int start = 1, end = 9;
     //int mid = (start + end) / 2;
     //while(mid)
     class BigNumber bigtemp(tempt);
     for(int i = 9; i >= 1; i--){
          BigNumber temp = mult[i];
          if(bigtemp >= temp)//有算degree??
               return i;
     }
     return -1;
}

void divide(string ts, string ds, string& ans){
     int ts_size = ts.size();
     int ds_size = ds.size();
     BigNumber ts_B = BigNumber(ts);

     vector<class BigNumber> mult(10);
     BigNumber ds_Big = BigNumber(ds);
     for(int i = 1; i < 10; i++){
          mult[i] = BigNumber(i) * ds_Big;
     }

     string tempt;
     const int MAX_ANS_DEGREE = ts_size - ds_size + 1;
     for(int i = 0 ; i < MAX_ANS_DEGREE; i++){
          if(ts.size() < ds_size)
               break;
          tempt.assign(ts, 0, ds_size);//先取ds_size個數的數
          //printf("tempt = %s\n", tempt.c_str());
          if(tempt >= ds){//被除數較大
               int g = new_guxuan(tempt, mult);
               ans.push_back('0' + g);
               ts_B = ts_B - (BigNumber(g) * ds_Big);
               ts = ts_B.get_string_number();
          } else {//被除數較小
               if(ts.size() == ds_size)//同長度，且被除數較小
                    break;
               //加一位，再算
               i++;
               ans.push_back('0');
               tempt.push_back(ts[ds_size]);

               int g = new_guxuan(tempt, mult);
               ans.push_back('0' + g);
               ts_B = ts_B - (BigNumber(g) * ds_Big);
               ts = ts_B.get_string_number();
          }
     }
     //補齊0？
     int ans_size = ans.size();
     for(i = 0; i < MAX_ANS_DEGREE - ans_size; i++){
          ans.push_back('0');
     }
}

BigNumber BigNumber::operator/(BigNumber devidend){//not sure
     int loa = this->vec2.size();
     int lob = devidend.vec2.size();
     int lo = (loa>lob)?loa:lob;

     if(devidend.num_str == "0"){
          puts("Invalid: Divide by zero");
          return BigNumber();
     } else if(this->num_str == "0" || loa < lob){//除數 = 0？
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
     divide(this->num_str, devidend.num_str, ans);
     if(isneg){
          ans.insert(0, "-");
     }
     return BigNumber(ans);//!! plus negative
}
