#include "Punto.h"
#include <iostream>

using namespace std;

int  main(int argc, char const *argv[]) {
  punto p(0,0);
  cout<<"x="<<p.getx()<<"y="<<p.gety()<<endl;
  p++;
  cout<<"p++"<<endl;
  cout<<"x="<<p.getx()<<"y="<<p.gety()<<endl;
  p=p+1;
  cout<<"p=p+1"<<endl;
  cout<<"x="<<p.getx()<<"y="<<p.gety()<<endl;
  p=1+p;
  cout<<"p=1+p"<<endl;
  cout<<"x="<<p.getx()<<"y="<<p.gety()<<endl;
  punto c(1,2);
  p=c;
  cout<<"p=c"<<endl;
  cout<<"x="<<p.getx()<<"y="<<p.gety()<<endl;
  return 0;
}
