#ifndef __GRAFO_HPP__
#define __GRAFO_HPP__

#include <cassert>
#include <iostream>

using namespace std;

namespace ed
{

	template <class G_Nodo, class G_Lado>
	class Grafo
	{
	private:

		G_Lado **_lados;

		G_Nodo *_nodos;

	public:

		// constructores

		//constructor vacío
		//crea un grafo vacío
		inline Grafo(){
			_lados=NULL;
			_nodos=NULL;
		};

		//constructor con el número de nodos
		//Crea un grafo indicándole el número de nodos que tendrá
		inline Grafo(int const &n){
			G_Lado **lados;
			lados= new G_Lado *[n];
			for (int i = 0; i < n; i++) {
				lados[i]= new G_Lado [n];
			}
			this->setLados(lados);
			G_Nodo *nodos;
			nodos=new G_Nodo [n];
			this->setNodos(nodos);
		};

		//constructor de copia
		//Crea un grafo con la misma información que otro
		inline Grafo(Grafo const &g){
			*this=g;
		};

		// destructor

		inline ~Grafo(){
			this->borrarGrafo();
		};

		//observadores y modificadores

		//modificador de la variable lados
		inline void setLados(G_Lado **lados){
				_lados=lados;
		};

		//observador de la variable lados
		inline G_Lado **getLados() const {
			return _lados;
		};

		//modificador de la varibale nodos
		inline void setNodos(G_Nodo *nodos){
				_nodos=nodos;
		};

		//observador de la variable nodos
		inline G_Nodo *getNodos() const {
			return _nodos;
		};

		// funciones

		// función que borra el grafo
		void borrarGrafo(){
			G_Lado **lados=_lados;
			G_Nodo *nodos=_nodos;
			int nColumnas=sizeof(nodos)/sizeof(G_Nodo);
			for (int i = 0; i < nColumnas; i++) {
				delete[] lados[i];
			}
			delete[] lados;
			delete[] nodos;
			_lados=NULL;
			_nodos=NULL;
		}

		//operadores

		//operador de igualdad
		Grafo & operator=(Grafo const &g){
			G_Nodo *gNodos=g._nodos;
			G_Lado **gLados=g._lados;
			int n=sizeof(gNodos)/sizeof(G_Nodo);

			G_Nodo *nodos;
			nodos=new G_Nodo [n];
			G_Lado **lados;
			lados=new G_Lado *[n];
			for (int i = 0; i < n; i++) {
				lados[i]=new G_Lado [n];
			}
			for (int i = 0; i < n; i++) {
				nodos[i]=gNodos[i] ;
			}
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					lados[i][j]=gLados[i][j];
				}
			}

			_nodos=nodos;
			_lados=lados;
			return *this;
		}


	};
}

#endif
