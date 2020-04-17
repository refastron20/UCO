#include <iostream>
#include <cstdlib> //para usar srand()
#include <cstdio>
//#include <ctype>

#include "arbolbinarioordenadoenlazado.hpp"
#include "operadornodo.hpp"
#include "persona.hpp"
#include "generarpersona.hpp"
#include "macros.hpp"

using namespace ed;

int main()
{
  std::cout << CLEAR_SCREEN;
  srand(time(0));
  ArbolBinarioOrdenadoEnlazado<int> a;
  int opcion=0;
  int posicion=2;
  //int ninserciones=0;
  int p=0;

  while(opcion!=6){
    posicion=2;
    int n;
    //char nombre[50], apellido[50];
    //int dni;
    EscribirNodo<int> operador;

    PLACE(posicion++,10);
  	std::cout << BIBLUE;
  	std::cout << "Opciones del menú: ";
  	std::cout << RESET;

    posicion++;
    PLACE(posicion++,10);
  	std::cout << PURPLE;
  	std::cout << "1) Insertar numeros" << '\n';
    PLACE(posicion++,10);
    std::cout << "2) Comprobar existencia de una persona en el árbol" << '\n';
    PLACE(posicion++,10);
    std::cout << "3) Mostrar elementos del árbol" << '\n';
    PLACE(posicion++,10);
    std::cout << "4) Borrar una persona del árbol" << '\n';
    PLACE(posicion++,10);
    std::cout << "5) Borrar el árbol" << '\n';
    PLACE(posicion++,10);
    std::cout << "6) Salir" << '\n';
  	std::cout << RESET;

    posicion++;
    PLACE(posicion++,10);
    std::cin>>opcion;

    std::cout << CLEAR_SCREEN;


    switch(opcion){
      case 1:
        /*posicion++;

        posicion++;
        PLACE(posicion++,10);
        std::cout << BIGREEN;
        std::cout << "¿Cuántas personas quiere introducir?" << '\n';
        std::cout <<  RESET;

        posicion++;
        PLACE(posicion++,10);
        std::cin>>n;

        ninserciones+=n;

        for (int i = 0; i < n; i++) {
          p=generarDatosPersonales();
          a.insertar(p);
          posicion++;
          PLACE(posicion++,10);
          std::cout << BIBLUE;
          std::cout << "Introduciendo a: " << '\n';
          std::cout <<  RESET;
          p.mostrarPersona();
        }*/

        posicion++;
        PLACE(posicion++,10);
        std::cout << BIGREEN;
        std::cout << "Insertando datos..." << '\n';
        std::cout <<  RESET;

        a.insertar(10);
        a.insertar(5);
        a.insertar(1);
        a.insertar(9);
        a.insertar(7);
        a.insertar(6);
        a.insertar(8);
        a.insertar(20);
        a.insertar(15);
        a.insertar(25);
        a.insertar(22);
        a.insertar(27);
        posicion++;
        posicion++;
        PLACE(posicion++,10);
        std::cout << BIGREEN;
        std::cout << "Para continuar, pulse ";
      	std::cout << INVERSE ;
      	std::cout << "ENTER";
      	std::cout << RESET;

      	// Pausa
        std::cin.ignore();
      	std::cin.ignore();
        std::cout << CLEAR_SCREEN;
      break;

      case 2:{
        /*posicion++;
        PLACE(posicion++,10);
        std::cout << BIGREEN;
        std::cout << "Introduzca los datos de la persona a buscar" << '\n';
        std::cout << RESET;
        PLACE(posicion++,10);
        std::cout<<BICYAN;
        std::cout << " Nombre" << '\n';
        std::cout << RESET;
        PLACE(posicion++,10);
        std::cin >> nombre;
        PLACE(posicion++,10);
        std::cout<<BICYAN;
        std::cout << " Apellido" << '\n';
        std::cout << RESET;
        PLACE(posicion++,10);
        std::cin >> apellido;
        PLACE(posicion++,10);
        std::cout<<BICYAN;
        std::cout << " DNI" << '\n';
        std::cout << RESET;
        PLACE(posicion++,10);
        std::cin >> dni;

        for (int indice = 0; nombre[indice] != '\0'; ++indice){
		        nombre[indice] = toupper(nombre[indice]);
	      }
        for (int indice = 0; apellido[indice] != '\0'; ++indice){
		        apellido[indice] = toupper(apellido[indice]);
	      }
        p.nombre(nombre);
        p.apellido(apellido);
        p.dni(dni);
        */

        posicion++;
        PLACE(posicion++,10);
        std::cout << BIGREEN;
        std::cout << "Introduzca el entero a buscar" << '\n';
        std::cout << RESET;
        PLACE(posicion++,10);
        std::cin >> p;

        if (a.buscar(p)) {
          posicion++;
          PLACE(posicion++,10);
          std::cout<<BIBLUE;
          std::cout << "Encontrado" << '\n';
          std::cout<<RESET;
        }else{
          posicion++;
          PLACE(posicion++,10);
          std::cout<<BIRED;
          std::cout << "No encontrado" << '\n';
          std::cout<<RESET;
        }

        posicion++;
        posicion++;
        PLACE(posicion++,10);
        std::cout << BIGREEN;
        std::cout << "Para continuar, pulse ";
      	std::cout << INVERSE ;
      	std::cout << "ENTER";
      	std::cout << RESET;

      	// Pausa
        std::cin.ignore();
        std::cin.ignore();
        std::cout << CLEAR_SCREEN;
      break;}

      case 3:
        posicion++;
        PLACE(posicion++,10);
        std::cout<<BIGREEN;
        std::cout<<"Arbol en recorrido preorden:"<<std::endl;
        std::cout<<RESET;
        a.recorridoPreOrden(operador);

        posicion+=3;
        PLACE(posicion++,10);
        std::cout<<BIGREEN;
        std::cout<<"Arbol en recorrido postorden:"<<std::endl;
        std::cout<<RESET;
        a.recorridoPostOrden(operador);

        posicion+=3;
        PLACE(posicion++,10);
        std::cout<<BIGREEN;
        std::cout<<"Arbol en recorrido inorden:"<<std::endl;
        std::cout<<RESET;
        a.recorridoInOrden(operador);

        posicion+=3;
        posicion++;
        PLACE(posicion++,10);
        std::cout << BIGREEN;
        std::cout << "Para continuar, pulse ";
      	std::cout << INVERSE ;
      	std::cout << "ENTER";
      	std::cout << RESET;

      	// Pausa
        std::cin.ignore();
        std::cin.ignore();
        std::cout << CLEAR_SCREEN;
      break;

      case 4:
        /*posicion++;
        PLACE(posicion++,10);
        std::cout << BIGREEN;
        std::cout << "Introduzca los datos de la persona a borrar" << '\n';
        std::cout << RESET;
        PLACE(posicion++,10);
        std::cout<<BICYAN;
        std::cout << " Nombre" << '\n';
        std::cout << RESET;
        PLACE(posicion++,10);
        std::cin >> nombre;
        PLACE(posicion++,10);
        std::cout<<BICYAN;
        std::cout << " Apellido" << '\n';
        std::cout << RESET;
        PLACE(posicion++,10);
        std::cin >> apellido;
        PLACE(posicion++,10);
        std::cout<<BICYAN;
        std::cout << " DNI" << '\n';
        std::cout << RESET;
        PLACE(posicion++,10);
        std::cin >> dni;

        for (int indice = 0; nombre[indice] != '\0'; ++indice){
            nombre[indice] = toupper(nombre[indice]);
        }
        for (int indice = 0; apellido[indice] != '\0'; ++indice){
            apellido[indice] = toupper(apellido[indice]);
        }
        p.nombre(nombre);
        p.apellido(apellido);
        p.dni(dni);
        */

        posicion++;
        PLACE(posicion++,10);
        std::cout << BIGREEN;
        std::cout << "Introduzca el entero a borrar" << '\n';
        std::cout << RESET;
        PLACE(posicion++,10);
        std::cin >> p;

        if (a.buscar(p)) {
          posicion++;
          PLACE(posicion++,10);
          std::cout<<BIBLUE;
          std::cout << "¿Esta seguro que quiere borrar el entero?(1=sí/0=no)" << '\n';
          PLACE(posicion++,10);
          std::cout << p << '\n';
          std::cout<<RESET;
          //p.mostrarPersona();
          posicion++;
          PLACE(posicion++,10);
          std::cin>>p;
          if (p==1) {
            posicion++;
            PLACE(posicion++,10);
            std::cout<<BIBLUE;
            std::cout << "borrando..." << '\n';
            std::cout<<RESET;
            a.borrar();
          }else{
            posicion++;
            PLACE(posicion++,10);
            std::cout<<BIBLUE;
            std::cout << "Ha cancelado el borrado" << '\n';
            std::cout<<RESET;
          }
        }else{
          posicion++;
          PLACE(posicion++,10);
          std::cout<<BIRED;
          std::cout << "La persona que ha introducido no existe" << '\n';
          std::cout<<RESET;
        }

        posicion++;
        posicion++;
        PLACE(posicion++,10);
        std::cout << BIGREEN;
        std::cout << "Para continuar, pulse ";
      	std::cout << INVERSE ;
      	std::cout << "ENTER";
      	std::cout << RESET;

      	// Pausa
        std::cin.ignore();
        std::cin.ignore();
        std::cout << CLEAR_SCREEN;


      break;

      case 5:
        posicion++;
        PLACE(posicion++,10);
        std::cout<<BIRED;
        std::cout << "¿Está seguro que quiere borrar el árbol?(1=sí/0=no)" << '\n';
        std::cout<<RESET;
        PLACE(posicion++,10);
        std::cin >> n;

        if (n==1) {
          posicion++;
          PLACE(posicion++,10);
          std::cout<<BIBLUE;
          std::cout << "Borrando árbol..." << '\n';
          std::cout<<RESET;
          a.borrarArbol();
        }else{
          posicion++;
          PLACE(posicion++,10);
          std::cout<<BIRED;
          std::cout << "Ha cancelado el borrado del árbol" << '\n';
          std::cout<<RESET;
        }

        posicion++;
        posicion++;
        PLACE(posicion++,10);
        std::cout << BIGREEN;
        std::cout << "Para continuar, pulse ";
      	std::cout << INVERSE ;
      	std::cout << "ENTER";
      	std::cout << RESET;

      	// Pausa
        std::cin.ignore();
        std::cin.ignore();
        std::cout << CLEAR_SCREEN;
      break;

      case 6:
        PLACE(posicion++,10);
        std::cout << BIGREEN;
        std::cout << "Para salir, pulse ";
        std::cout << INVERSE ;
        std::cout << "ENTER";
        std::cout << RESET;

        // Pausa
        std::cin.ignore();
        std::cin.ignore();
        std::cout << CLEAR_SCREEN;
      break;

      default:
        posicion++;
        PLACE(posicion++,10);
        std::cout<<BIRED;
        std::cout << "Elija una opción válida" << '\n';
        std::cout<<RESET;

        posicion++;
        posicion++;
        PLACE(posicion++,10);
        std::cout << BIGREEN;
        std::cout << "Para continuar, pulse ";
      	std::cout << INVERSE ;
      	std::cout << "ENTER";
      	std::cout << RESET;

      	// Pausa
        std::cin.ignore();
        std::cin.ignore();
        std::cout << CLEAR_SCREEN;
      break;
    }
  }

  posicion++;
  PLACE(posicion++,10);
  std::cout<<BIRED;
  std::cout << "Saliendo..." << '\n';
  std::cout<<RESET;
}
