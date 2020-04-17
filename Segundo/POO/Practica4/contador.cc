#include "contador.h"
#include <iostream>

using namespace std;

bool Contador::undo(int n){
  if((unsigned int)n>(undo_.size()-1))
    return false;
  for (int i = 0; i < n; i++){
    undo_.pop_back();
  }
  valor_=undo_.back();
  return true;
}

Contador Contador:: operator=(int n){
  if(n>=max_){
    valor_=max_;
  }else{
    if(n<=min_)
      valor_=min_;
    else
      valor_=n;
  }
  undo_.push_back(valor_);
  return *this;
}

Contador Contador:: operator=(const Contador &c){
  valor_=c.valor_;
  min_=c.min_;
  max_=c.max_;
  undo_.push_back(valor_);
  return *this;
}

Contador Contador:: operator++(void){//prefijo ++c
  if(valor_==max_){
    undo_.push_back(valor_);
    return *this;
  }else{
    valor_++;
    undo_.push_back(valor_);
    return *this;
  }
}

Contador Contador:: operator++(int){//postfijo c++
  Contador a=*this;
  if(valor_>=max_){
    undo_.push_back(valor_);
    return a;
  }else{
    valor_++;
    undo_.push_back(valor_);
    return a;
  }
}

Contador Contador::operator--(void){//prefijo --c
  if(valor_==min_){
    undo_.push_back(valor_);
    return *this;
  }else{
    valor_--;
    undo_.push_back(valor_);
    return *this;
  }
}

Contador Contador::operator--(int){//postfijo c--
  Contador a=*this;
  if(valor_==min_){
    undo_.push_back(valor_);
    return a;
  }else{
    valor_--;
    undo_.push_back(valor_);
    return a;
  }
}

Contador Contador::operator+(int n){
  Contador c=*this;
  if((c.valor_+n)>c.max_){
    c.valor_=c.max_;
    undo_.push_back(valor_);
    return c;
  }else{
    c.valor_=this->valor_+n;
    undo_.push_back(valor_);
    return c;
  }
}

Contador operator+(int n, const Contador &c){
  Contador aux=c;
  if((n+c.valor_)>c.max_){
    aux.valor_=c.max_;
    aux.undo_.push_back(aux.valor_);
    return aux;
  }else{
    aux.valor_=c.valor_+n;
    aux.undo_.push_back(aux.valor_);
    return aux;
  }
}

Contador Contador::operator-(int n){
  undo_.push_back(valor_);
  Contador c=*this;
  if((c.valor_-n)<c.min_){
    c.valor_=c.min_;
    return c;
  }else{
    c.valor_=this->valor_-n;
    return c;
  }
}

Contador operator-(int n, const Contador &c){
  Contador aux=c;
  if((n-c.valor_)<c.min_){
    aux.valor_=c.min_;
    aux.undo_.push_back(aux.valor_);
    return aux;
  }else{
    aux.valor_=c.valor_-n;
    aux.undo_.push_back(aux.valor_);
    return aux;
  }
}
