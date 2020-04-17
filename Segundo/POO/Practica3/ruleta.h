

#ifndef RULETA_H
#define RULETA_H

#include "crupier.h"
#include "jugador.h"
#include <list>

class Ruleta : public Crupier{
private:
  int banca_;
  int bola_;
  list <Jugador> jugadores_;
  Crupier crupier_;
public:
  inline Ruleta(Crupier c){bola_=-1;banca_=1000000;crupier_=c;};
  inline const void getBanca(){return banca_;};
  inline bool setBanca(int banca){if(banca>0){banca_=banca;return true;}else{return false;}};
  inline const void getBola(){return bola_;};
  inline bool setBola(int bola){if(bola>=0&&bola<=36){bola_=bola;return true;}else{return false;}};
  inline const void getCrupier(){return crupier_;};
  inline void setCrupier(Crupier crupier){crupier_=crupier;};
  inline const void getJugadores(){return jugadores_;};
  bool addjugador(Jugador jugador);
  inline int deleteJugador(){return 1;};
  inline void escribeJugadorea(){printf("hola\n" );};

};




#endif
