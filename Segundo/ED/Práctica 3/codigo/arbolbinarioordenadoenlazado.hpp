#ifndef __ARBOLBINARIOORDENADO_HPP__
#define __ARBOLBINARIOORDENADOENLAZADO_HPP__

#include <iostream>
#include <cassert>
#include "arbolbinarioordenado.hpp"
#include "operadornodo.hpp"

using namespace std;
/*!
\brief Espacio de nombres para la asignatura Estructura de datos.
*/
namespace ed
{
	/*!\brief Interfaz para definir un ArbolBinario ordenado.

	Define una interfaz para definir un ArbolBinarioOrdenado.

	\arg G define el campo de información a contener en el arbol.
	\pre G debe tener definidos los operadores < y ==.
	*/
	template<class G>
	class ArbolBinarioOrdenadoEnlazado:public ArbolBinarioOrdenado<G>
	{
	private:

		/*!\brief Define un nodo del arbol binario.*/
		class NodoArbolBinario
		{
		private:
			G _info;  //Valor informativo almacenado en el nodo
			NodoArbolBinario * _izquierdo;  //Puntero al hijo izquierdo
			NodoArbolBinario * _derecho;  //Puntero al hijo derecho

		public:
			NodoArbolBinario (const G &info)
			{
				this->setInfo(info);

				#ifndef NDEBUG
					assert(this->getIzquierdo()==NULL);
					assert(this->getDerecho()==NULL);
				#endif
			}

			NodoArbolBinario (const NodoArbolBinario &n)
			{
				*this=n;

				#ifndef NDEBUG
					assert(this->getInfo()==n.getInfo());
					assert(this->getDerecho()==n.getDerecho());
					assert(this->getIzquierdo()==n.getIzquierdo());
				#endif
			}

			/*!\brief Observadores.*/
			const G & getInfo() const
			{
				return _info;
			}

			NodoArbolBinario *getIzquierdo() const
			{
				return _izquierdo;
			}

			NodoArbolBinario *getDerecho() const
			{
				return _derecho;
			}

			bool esHoja() const
			{
				if (this->getDerecho()==NULL and this->getIzquierdo()==NULL) {
					return true;
				}else{
					return false;
				}
			}

			void recorridoPreOrden (OperadorNodo<G> &operador) const
			{
				operador.aplicar(this->getInfo());
				if (this->getIzquierdo()) {
					this->getIzquierdo()->recorridoPreOrden(operador);
				}
				if (this->getDerecho()) {
					this->getDerecho()->recorridoPreOrden(operador);
				}
			}

			void recorridoPostOrden (OperadorNodo<G> &operador) const
			{

					if (this->getIzquierdo()!=NULL) {
						this->getIzquierdo()->recorridoPostOrden(operador);
					}
					if (this->getDerecho()!=NULL) {
						this->getDerecho()->recorridoPostOrden(operador);
					}
					operador.aplicar(this->getInfo());

			}

			void recorridoInOrden (OperadorNodo<G> &operador) const
			{
				if (this->getIzquierdo()!=NULL) {
					this->getIzquierdo()->recorridoInOrden(operador);
				}
					operador.aplicar(this->getInfo());
				if (this->getDerecho()!=NULL) {
					this->getDerecho()->recorridoInOrden(operador);
				}
			}

			/*!\brief Modificadores. */
			void setInfo(const G &info)
			{
				_info=info;

				#ifndef NDEBUG
					assert(_info==info);
				#endif
			}

			void setIzquierdo(NodoArbolBinario *n)
			{
				_izquierdo=n;

				#ifndef NDEBUG
					assert(_izquierdo==n);
				#endif
			}

			void setDerecho(NodoArbolBinario *n)
			{
				_derecho=n;

				#ifndef NDEBUG
					assert(_derecho==n);
				#endif
			}

			NodoArbolBinario & operator=(const NodoArbolBinario &n)
			{
				#ifndef NDEBUG
					assert(this->getInfo()!=n.getInfo());
					assert(this->getIzquierdo()!=n.getIzquierdo());
					assert(this->getDerecho()!=n.getDerecho());
				#endif

				this->setInfo(n.getInfo());
				this->setIzquierdo(n.getIzquierdo());
				this->setDerecho(n.getDerecho());

				#ifndef NDEBUG
					assert(this->getInfo()==n.getInfo());
					assert(this->getIzquierdo()==n.getIzquierdo());
					assert(this->getDerecho()==n.getDerecho());
				#endif

				return *this;
			}

		}; //Fin clase NodoArbolBinario

		//Implementación de la raíz
		NodoArbolBinario * _raiz; /*!<La raiz del árbol*/
		NodoArbolBinario * _actual; /*!<Cursor al nodo actual*/
		NodoArbolBinario * _padre; /*!<Cursor al nodo padre de actual*/

		//modificador de la raíz
		void setRaiz(NodoArbolBinario *raiz){
			_raiz=raiz;
		}

		//observador de la raíz
		NodoArbolBinario *getRaiz() const {
			return _raiz;
		}

		//modificador de actual
		void setActual(NodoArbolBinario *actual){
			_actual=actual;
		}

		//observador de actual
		NodoArbolBinario *getActual() const {
			return _actual;
		}

		//modificador de padre
		void setPadre(NodoArbolBinario *padre){
			_padre=padre;
		}

		//observador de padre
		NodoArbolBinario *getPadre() const {
			return _padre;
		}

	public:

		ArbolBinarioOrdenadoEnlazado ()
		{
			this->setRaiz(NULL);
			this->setActual(NULL);
			this->setPadre(NULL);

			#ifndef NDEBUG
				assert(this->estaVacio());
			#endif
		}

		ArbolBinarioOrdenadoEnlazado (const ArbolBinarioOrdenadoEnlazado<G>& a)
		{
			*this=a;
			#ifndef NDEBUG
				assert(not this->estaVacio());
			#endif
		}

		~ArbolBinarioOrdenadoEnlazado ()
		{
			if (not this->estaVacio())
				borrarArbol();
			cout << "Destructor Usado \n";
		}

		ArbolBinarioOrdenadoEnlazado &operator=(const ArbolBinarioOrdenadoEnlazado& a)
		{
			this->setRaiz(a.getRaiz());
			this->setPadre(a.getPadre());
			this->setActual(a.getActual());
		}

		bool insertar(const G &x)
		{
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//Si está vacío se inserta en la raíz
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			if (this->estaVacio()) {
				this->setRaiz(new NodoArbolBinario(x));
				this->setActual(this->getRaiz());
				this->setPadre(NULL);
				#ifndef NDEBUG
					assert(this->actual()==x);
				#endif
				return true;
			}

			//~~~~~~~~~~~~~~~~~~~~~~~~~~
			//Si ya existe no se inserta
			//~~~~~~~~~~~~~~~~~~~~~~~~~~
			if (this->buscar(x)){
				#ifndef NDEBUG
					assert(this->actual()==x);
				#endif
				return true;
			}

			//Apunto el actual a la raíz para empezar a recorrer el árbol desde ella
			this->setActual(this->getRaiz());
			this->setPadre(NULL);
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//Se repite el bucle hasta que se inserte el ítem
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			while(1){
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				//Si es mayor que el actual voy por el hijo derecho
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				if (x>this->actual()) {
					//Si el hijo derecho no existe se inserta el ítem
					if(this->getActual()->getDerecho()==NULL){
						this->getActual()->setDerecho(new NodoArbolBinario(x));
						this->setPadre(this->getActual());
						this->setActual(new NodoArbolBinario(x));
						#ifndef NDEBUG
							assert(this->actual()==x);
						#endif
						return true;
					//si existe se pasa el actual al hijo derecho
					}else{
						this->setPadre(this->getActual());
						this->setActual(this->getActual()->getDerecho());
					}
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				//Si es menor que el actual voy por el hijo derecho
				//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				}else{
					//Si el hijo izquierdo no existe se inserta el ítem
					if (this->getActual()->getIzquierdo()==NULL){
						this->getActual()->setIzquierdo(new NodoArbolBinario(x));
						this->setPadre(this->getActual());
						this->setActual(new NodoArbolBinario(x));
						#ifndef NDEBUG
							assert(this->actual()==x);
						#endif
						return true;
					//si existe se pasa el actual al hijo izquierdo
					}else{
						this->setPadre(this->getActual());
						this->setActual(this->getActual()->getIzquierdo());
					}
				}
			}
		}

		void borrarArbol()
		{
			this->setRaiz(NULL);
			this->setActual(NULL);
			this->setPadre(NULL);
		}

		bool borrar()
		{
			#ifndef NDEBUG
				assert(this->getActual()!=NULL);
				G aserto=this->actual();
			#endif
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//Caso de que sea raíz y hoja
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~
			if (this->getActual()==this->getRaiz()) {
				this->borrarArbol();
				return true;
			}

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//caso de que se quiera borrar una hoja
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			if (this->getActual()->esHoja()) {
				//comprobamos si es el hijo izquierdo o derecho
					if (this->getActual()->getInfo()>this->getPadre()->getInfo()){
						//buscamos el padre para que el puntero actual apunte al padre y el puntero padre al padre del padre
						this->buscar(this->getPadre()->getInfo());
						//como el nodo a borrar era mayor a su padre ponemos a NULL el puntero que apunta al nodo derecho
						this->getActual()->setDerecho(NULL);
						#ifndef NDEBUG
							assert(not this->buscar(aserto));
						#endif
						return true;
					}else{
						if (this->getActual()->getInfo()<this->getPadre()->getInfo()) {
							//buscamos el padre para que el puntero actual apunte al padre y el puntero padre al padre del padre
							this->buscar(this->getPadre()->getInfo());
							//como el nodo a borrar era menor a su padre ponemos a NULL el puntero que apunta al nodo izquierdo
							this->getActual()->setIzquierdo(NULL);
							#ifndef NDEBUG
								assert(not this->buscar(aserto));
							#endif
							return true;
						}
					}
			}

			//~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//Caso de que no sea una hoja
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~

			//guardamos la dirección del actual y del padre
			bool flag=false;
			NodoArbolBinario *auxactual, *auxpadre;
			auxactual=this->getActual();
			auxpadre=this->getPadre();
			//si tiene hijo derecho aplicaremos el recorrido de una vez a la derecha y todo a la izquierda
			if(this->getActual()->getDerecho()!=NULL){
				this->setPadre(this->getActual());
				this->setActual(this->getActual()->getDerecho());
				//ahora recorremos todo lo que podamos hacia la izquierda
				while(this->getActual()->getIzquierdo()!=NULL){
					flag=true;
					this->setPadre(this->getActual());
					this->setActual(this->getActual()->getIzquierdo());
				}
				//Guardamos su info
				G aux=this->getActual()->getInfo();
				//comprobamos si tiene hijo derecho
				if (this->getActual()->getDerecho()!=NULL) {
					//si tiene hijo derecho hacemos que el padre pase a apuntar al nodo hijo
					if (!flag) {
						this->getPadre()->setDerecho(this->getActual()->getDerecho());
					}else{
						this->getPadre()->setIzquierdo(this->getActual()->getDerecho());
					}
				}
				this->setActual(auxactual);
				this->setPadre(auxpadre);
				this->getActual()->setInfo(aux);
				#ifndef NDEBUD
					assert(not this->buscar(aserto));
				#endif
				return true;
			//si solo tiene hijo izquierdo haremos lo contrario
			}else{
				this->setPadre(this->getActual());
				this->setActual(this->getActual()->getIzquierdo());
				//ahora recorremos todo lo que podamos hacia la izquierda
				while(this->getActual()->getDerecho()!=NULL){
					flag=true;
					this->setPadre(this->getActual());
					this->setActual(this->getActual()->getDerecho());
				}
				//Guardamos su info
				G aux=this->getActual()->getInfo();
				//comprobamos si tiene hijo Izquierdo
				if (this->getActual()->getIzquierdo()!=NULL) {
					//si tiene hijo derecho hacemos que el padre pase a apuntar al nodo hijo
					if (flag) {
						this->getPadre()->setDerecho(this->getActual()->getIzquierdo());
					}else{
						this->getPadre()->setIzquierdo(this->getActual()->getIzquierdo());
					}
				}
				//devolvemos los punteros a su inicio
				this->setActual(auxactual);
				this->setPadre(auxpadre);
				//cambiamos la información del puntero
				this->getActual()->setInfo(aux);
				#ifndef NDEBUD
					assert(not this->buscar(aserto));
				#endif
				return true;
			}
		}

		void recorridoPreOrden (OperadorNodo<G> &operador) const
		{
			if (not estaVacio())
			{
				// Invocamos a la función recorridoPreOrden de nodo desde la raiz
				this->getRaiz()->recorridoPreOrden(operador);
			}
		}

		void recorridoPostOrden (OperadorNodo<G> &operador) const
		{
			if (not estaVacio())
			{
				// Invocamos a la función recorridoPostOrden de nodo desde la raiz
				this->getRaiz()->recorridoPostOrden(operador);
			}
		}

		void recorridoInOrden (OperadorNodo<G> &operador) const
		{
			if (not estaVacio())
			{
				// Invocamos a la función recorridoInOrden de nodo desde la raiz
				this->getRaiz()->recorridoInOrden(operador);
			}
		}

		//función de búsqueda
		bool buscar(const G& x)
		{
			//si está vacío el árbol se devuelve false directamente
			if (this->estaVacio()) {
				return false;
			}
			//se sitúa el actual en la raíz
			this->setPadre(NULL);
			this->setActual(this->getRaiz());
			while(1){
				//si actual es igual a lo que buscamos
				if (x==this->actual()) {
					#ifndef NDEBUG
						assert(x==this->actual());
					#endif
					return true;
				//si el elemento buscado es mayor que el actual continuamos por la derecha
				}else if(x>this->actual()){
					//si yo no hay mas hijos a la derecha es que no existe el elemento
					if (this->getActual()->getDerecho()==NULL) {
						return false;
					}
					this->setPadre(this->getActual());
					this->setActual(this->getActual()->getDerecho());
				//si el elemento buscado es menor que el actual continuamos por la izquierda
				}else{
					//si yo no hay mas hijos a la izquierda es que no existe el elemento
					if (this->getActual()->getIzquierdo()==NULL) {
						return false;
					}
					this->setPadre(this->getActual());
					this->setActual(this->getActual()->getIzquierdo());
				}
			}
		}

		bool estaVacio() const
		{
			//si la raiz está a NULL es que no hay ningún elemento en el árbol
			if (this->getRaiz()==NULL and this->getActual()==NULL and this->getPadre()==NULL) {
				return true;
			}
			return false;
		}

		G raiz() const
		{
			#ifndef NDEBUG
				assert(not this->estaVacio());
			#endif
			//devolvemos la info de la raíz
			return this->getRaiz()->getInfo();
		}

		bool existeActual() const
		{
			#ifndef NDEBUG
				assert(!(this->estaVacio()));
			#endif
			//si actual está a NULL es que no existe el actual
			if (this->getActual()==NULL)
				return false;

			return true;
		}

		G actual() const
		{
			#ifndef NDEBUG
				assert(not (this->getActual()==NULL));
			#endif
			//devolvemos la info de actual
			return this->getActual()->getInfo();
		}

		/*!@}*/
	};

} //namespace ed

#endif //__ARBOLORDENADO_HPP__
