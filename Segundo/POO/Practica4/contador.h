#include <list>

#ifndef CONTADOR_H
#define CONTADOR_H

using namespace std;

class Contador{
private:
  int valor_;
  int min_;
  int max_;
  list <int> undo_;

public:
  inline Contador(int valor=0,int min=0, int max=1000){
    if(valor<min||valor>max||min>max){
      valor_=0;
      undo_.push_back(valor_);
      min_=0;
      max_=1000;
    }else{
      valor_=valor;
      undo_.push_back(valor_);
      min_=min;
      max_=max;
    }
  };

  inline int get(){return valor_;};

  bool undo(int n=1);

  Contador operator=(int n);
  Contador operator=(const Contador &c);
  Contador operator++(void);
  Contador operator++(int);
  Contador operator--(void);
  Contador operator--(int);
  Contador operator+(int n);
  friend Contador operator+(int n, const Contador &c);
  Contador operator-(int n);
  friend Contador operator-(int n, const Contador &c);

};


#endif
