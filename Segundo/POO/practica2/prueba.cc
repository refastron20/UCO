#include "ruleta.h"
#include <fstream>

int main(){
  Crupier c("33XX","crupier1");
  Jugador j1("44XX","jugador1");
  Jugador j2("55XX","jugador2");
  Ruleta r(c);
  r.addJugador(j1);
//  r.addJugador(j2);
  ofstream salida("44XX.txt");
  salida << 1 << "," << "10" << "," << 10<< "\n";
  salida << 2 << "," << "rojo" << "," << 20<< "\n";
  salida << 3 << "," << "par" << "," << 30<< "\n";
  salida << 4 << "," << "bajo" << "," << 40<< "\n";
  salida.close();

  salida.open("55XX.txt");
  salida << 2 << "," << "rojo" << "," << 50<< "\n";
  salida << 1 << "," << "15" << "," << 60<< "\n";
  salida << 4 << "," << "alto" << "," << 70<< "\n";
  salida << 3 << "," << "impar" << "," << 80<< "\n";
  salida.close();

  r.setBola(0); // jugadores pierden todo
  r.getPremios();
  //44XX -> 1000 - 10 - 20 - 30 - 40 = 900
  //55XX -> 1000 - 50 - 60 - 70 - 80 = 740
}
