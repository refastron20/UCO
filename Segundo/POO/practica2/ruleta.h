

#ifndef RULETA_H
#define RULETA_H

#include "crupier.h"
#include "jugador.h"
#include <list>
#include <ctime>

class Ruleta{
private:
  int banca_;
  int bola_;
  list <Jugador> jugadores_;
  Crupier crupier_;
public:
  inline Ruleta(Crupier c):crupier_(c){bola_=-1;banca_=1000000;srand(time(NULL));};
  inline int getBanca() const {return banca_;};
  inline bool setBanca(int banca){if(banca>0){banca_=banca;return true;}else{return false;}};
  inline int getBola() const {return bola_;};
  inline bool setBola(int bola){if(bola>=0&&bola<=36){bola_=bola;return true;}else{return false;}};
  inline Crupier getCrupier() const {return crupier_;};
  inline void setCrupier(Crupier crupier){crupier_=crupier;};
  inline list<Jugador> getJugadores() const {return jugadores_;};
  bool addJugador(Jugador jugador);
  int deleteJugador(Jugador jugador);
  int deleteJugador(string cad);
  void escribeJugadores();
  void leeJugadores();
  inline void giraRuleta(){bola_=rand()%37;};
  void getPremios();

};




#endif
