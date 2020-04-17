#include "Registro.h"
#include <iostream>

using namespace std;

int main(void){
  Registro r;
  int n;
  string str;
  cout<<"Cuantas ciudades quieres introducir"<<endl;
  cin>>n;
  for (int i = 0; i < n; i++) {
    Ciudad c("",0);
    cout<<"Nombre: ";
    cin>>str;
    c.setNombre(str);
    cout<<"Km2: ";
    cin>>str;
    c.setKm2(atoi(str.c_str()));
    r.InsertarCiudad(c);
  }
  cout<<"Cuantas personas quieres introducir"<<endl;
  cin>>n;
  for (int i = 0; i < n; i++) {
    Persona p("","","","");
    cout<<"Nombre: ";
    cin>>str;
    p.setNombre(str);
    cout<<"Apellido: ";
    cin>>str;
    p.setApellido(str);
    cout<<"DNI: ";
    cin>>str;
    p.setDNI(str);
    cout<<"Ciudad: ";
    cin>>str;
    p.setCiudad(str);
    r.InsertarPersona(p);
  }
  r.MostrarInfoCiudades();
  r.MostrarPersonas();
}
