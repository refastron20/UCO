#ifndef DOMINO_HPP
#define DOMINO_HPP

#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;
class Domino{
private:
 class Ficha{
 private:
   int der_;
   int izq_;
 public:
   inline Ficha(int der=0, int izq=0){izq_=izq;der_=der;};
   inline int getDer() const {return der_;};
   inline int getIzq() const {return izq_;};
   inline void setDer(int der){der_=der;};
   inline void setIzq(int izq){izq_=izq;};
   inline bool isDoble(){if(izq_==der_)return true;else return false;};
   friend bool  operator >(const Ficha f1, const Ficha f2){
     if (f1.getDer()>f2.getDer() and f1.getIzq() > f2.getIzq()) {
       return true;
     }else{
       return false;
     }
   };
   friend bool operator <(const Ficha f1, const Ficha f2){
     return !(f1>f2);
   }
   friend bool operator ==(const Ficha f1, const Ficha f2){
     if (f1.getDer()==f2.getDer() and f1.getIzq() == f2.getIzq()) {
       return true;
     }else{
       return false;
     }
   }

   friend bool operator !=(const Ficha f1, const Ficha f2){
     return !(f1==f2);
   }
 };

 vector <Ficha> monton_;
 vector <Ficha> mesa_;
 vector <Ficha> jugador1_;
 vector <Ficha> jugador2_;
public:
  Domino(){
    Ficha f;
    int pos,j=0;
    srand(time(NULL));
    vector <Ficha> montonAux;
    for (int i = 0; i < 7; i++) {
      f.setIzq(i);
      for (int j = 0; j < 7; j++) {
        f.setDer(j);
        montonAux.push_back(f);
      }
    }
    bool isFree[28];
    for (int i = 0; i < 28; i++) {
      isFree[i]=true;
    }
    while(j<28) {
      pos=rand()%28;
      if(isFree[pos]){
        monton_[pos]=montonAux[j];
        j++;
        isFree[pos]=false;
      }
    }
  }

  void repartirFichas(){
    for (int i = 0; i < 8; i++) {
      jugador1_.push_back(monton_[i]);
      jugador2_.push_back(monton_[i+8]);
    }
  }

  int empiezaTurno(){
    Ficha mayor1, mayor2;
    for (int i = 0; i < 8; i++) {
      if (jugador1_[i].isDoble() and jugador1_[i]>mayor1) {
        mayor1 = jugador1_[i];
      }
      if(jugador2_[i].isDoble() and jugador2_[i]>mayor2){
        mayor2 = jugador2_[i];
      }
    }
    Ficha zero(0,0);
    if (mayor2==mayor1==zero) {
      for (int i = 0; i < 8; i++) {
        if (jugador1_[i]) {
          mayor1 = jugador1_[i];
        }
        if(jugador2_[i]>mayor2){
          mayor2 = jugador2_[i];
        }
      }
    }

  }

};




#endif
