#include "ruleta.h"
#include "jugador.h"
#include <list>
#include <fstream>
#include <string>

using namespace std;

bool Jugador::addjugador(Jugador jugador){
  list<Jugador>::iterator i;
  i=jugador_.begin();
  while(!jugador_.end()){
    if((*i).getDNI()=jugador.getDNI())
      return false;
    i++;
  }
  jugador_.push_back(jugador);
  string filename=jugador.DNI()+".txt";
  ifstream file(filename.c_str());
  if(file.good())
    cout>>"El fichero se abrió\n";
  else
    cout>>"El fihcero no se abrio\n";
  file.close();
  return true;
}
