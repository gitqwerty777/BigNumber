#ifndef BIGNUMBER_TEMPLATE_H
#define BIGNUMBER_TEMPLATE_H

template <class T>
BigNumber::BigNumber(T template_init){
  string s;
  stringstream ss; 
  ss<<template_init;
  ss>>s;//read as string
  this->init(s);
}

//when you fully specialize something, it doesn't depend on a template parameter any more -- so unless you make the specialization inline, you need to put it in a .cpp file instead of a .h or you end up violating the one definition rule as David says. Note that when you partially specialize templates, the partial specializations do still depend on one or more template parameters, so they still go in a .h file.
//<http://stackoverflow.com/questions/4445654/multiple-definition-of-template-specialization-when-using-different-objects>
//<http://stackoverflow.com/questions/7883561/why-the-linker-complains-about-multiple-definitions-in-this-template>
template <>
inline BigNumber::BigNumber<string>(string s){
  this->init(s);
}

template <class T>
inline BigNumber BigNumber::operator= (T t){
  (*this) = BigNumber(t);// call template bignumber
  return (*this);
}

template <>
inline BigNumber BigNumber::operator= <BigNumber>(BigNumber replace){
  this->reset_number(replace.getString()); // why not use = ?
  return (*this);
}

#endif
