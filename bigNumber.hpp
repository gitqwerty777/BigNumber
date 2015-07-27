#ifndef BIGNUMBER_TEMPLATE_H
#define BIGNUMBER_TEMPLATE_H

template <class T>
BigNumber::BigNumber(T template_init){
  string s;
  stringstream ss; 
  ss<<template_init;
  ss>>s;
  this->init(s);
}

//when you fully specialize something, it doesn't depend on a template parameter any more -- so unless you make the specialization inline, you need to put it in a .cpp file instead of a .h or you end up violating the one definition rule as David says. Note that when you partially specialize templates, the partial specializations do still depend on one or more template parameters, so they still go in a .h file. <http://stackoverflow.com/questions/4445654/multiple-definition-of-template-specialization-when-using-different-objects>
template <>
inline BigNumber::BigNumber<string>(string s){
  this->init(s);
}

template <class T>
void BigNumber::operator= (T t){
  BigNumber tempbignumber(t);
  (*this) = tempbignumber;// call template bignumber
}

template <>
inline void BigNumber::operator= <BigNumber>(BigNumber replace){
  this->reset_number(replace.getString());
}

#endif
