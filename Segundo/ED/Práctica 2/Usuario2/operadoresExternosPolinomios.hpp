/*!
	\file operadoresExternosPolinomios.hpp
	\brief Ficheros con operadores de monomios y polinomios
*/

#ifndef _OperadoresPolinomios_HPP_
#define _OperadoresPolinomios_HPP_

// Facilita la entrada y salida
#include <iostream>

#include "Polinomio.hpp"

using std::istream;
using std::ostream;

// Espacio de nombre de la asigantura: ed
namespace ed
{

////////////////////////////////////////////////////////////////////////////
	// Funciones y operadores que no pertenecen a la clase Polinomio


	////////////////////////////////////////////////////////////
	//! \name Operadores de igualdad

	/*!
		\brief Comprueba  si  dos  polinomios  son  iguales: p1  ==  p2.Si  tienen  los  mismos monomios
		\param p1: primer polinomio a comparar
		\param p2: segundo polinomio a comparar
		\post El valor devuelto es verdadero si los dos polinomios tienen los mismos monomios
		\post El valor devuelto es falso, en caso contrario
		\return bool
	*/
	bool operator==(ed::Polinomio const & p1, ed::Polinomio const & p2);

	/*!
		\brief Comprueba  si  el  polinomio  “p”  es  igual  al  monomio  “m”,  es  decir,  si  el polinomio “p” tiene un único monomio que es igual a “m
		\note función inline
		\param p1: polinomio a comparar
		\param m: monomio a comparar
		\post El valor devuelto es verdadero si el polinomio tiene un único monomio que es igual a “m”
		\post El valor devuelto es falso, en caso contrario
		\return bool
	*/
	inline bool operator==(ed::Polinomio const & p1, ed::Monomio const & m){
		Polinomio aux;
		aux=m;
		return p1==aux;
	}

	/*!
		\brief Comprueba  si  el  polinomio  “p”  es  igual  al  monomio  “m”,  es  decir,  si  el polinomio “p” tiene un único monomio que es igual a “m
		\note función inline
		\param m: monomio a comparar
		\param p1: polinomio a comparar
		\post El valor devuelto es verdadero si el polinomio tiene un único monomio que es igual a “m”
		\post El valor devuelto es falso, en caso contrario
		\return bool
	*/
	inline bool operator==(ed::Monomio const & m, ed::Polinomio const & p1){
		return p1==m;
	}

	/*!
		\brief 	Comprueba si el polinomio “p” es igual al número “x”, es decir, si el polinomio “p” tiene un único monomio que es igual a “x”
		\note función inline
		\param p1: polinomio a comparar
		\param x: número a comparar
		\post El valor devuelto es verdadero verdadero si el polinomio tiene un único monomio que es igual a “x”
		\post El valor devuelto es falso, en caso contrario
		\return bool
	*/
	inline bool operator==(ed::Polinomio const & p1, double const & x){
		Monomio m(x);
		Polinomio aux;
		aux=m;
		return p1==aux;
	}

	/*!
		\brief 	Comprueba si el polinomio “p” es igual al número “x”, es decir, si el polinomio “p” tiene un único monomio que es igual a “x”
		\note función inline
		\param x: número a comparar
		\param p1: polinomio a comparar
		\post El valor devuelto es verdadero verdadero si el polinomio tiene un único monomio que es igual a “x”
		\post El valor devuelto es falso, en caso contrario
		\return bool
	*/
	inline bool operator==(double const & x, ed::Polinomio const & p1){
		return p1==x;
	}


	////////////////////////////////////////////////////////////////////////////////////
	//! \name Operadores de desigualdad

	/*!
		\brief Comprueba si dos polinomios no son iguales: p1 !=p2.Si no tienen los mismos monomios.
		\note función inline
		\param p1: polinomio a comparar
		\param p2: polinomio a comparar
		\post El valor devuelto es verdadero si los dos polinomios no tienen los mismos monomios
		\post El valor devuelto es falso, en caso contrario
		\return bool
	*/
	inline bool operator!=(ed::Polinomio const & p1, ed::Polinomio const & p2){
		return !(p1==p2);
	}

	/*!
		\brief Comprueba  si  el  polinomio  “p”  es  no  igual  al  monomio  “m”,  es  decir,  si  el polinomio “p” no tiene un único monomio que es igual a “m”
		\note función inline
		\param p1: polinomio a comparar
		\param m: monomio a comparar
		\post verdadero  si  el  polinomio  no  tiene  un  único  monomio  que  es  igual  a “m”
		\post El valor devuelto es falso, en caso contrario
		\return bool
	*/
	inline bool operator!=(ed::Polinomio const & p1, ed::Monomio const & m){
		return !(p1==m);
	}

	/*!
		\brief Comprueba  si  el  polinomio  “p”  no  es  igual  al monomio  “m”,  es  decir,  si  el polinomio “p” no tiene un único monomio que es igual a “m”
		\note función inline
		\param m: monomio a comparar
		\param p1: polinomio a comparar
		\post El valor devuelto es verdadero  si  el  polinomio  no  tiene  un  único  monomio  que  es  igual  a “m”
		\post El valor devuelto es falso, en caso contrario
		\return bool
	*/
	inline bool operator!=(ed::Monomio const & m, ed::Polinomio const & p1){
		return !(p1==m);
	}

	/*!
		\brief 	Comprueba  si  el  polinomio  “p”  no  es  igual  al  número  “x”,  es  decir,  si  el polinomio “p” no tiene un único monomio que es igual a “x”
		\note función inline
		\param p1: polinomio a comparar
		\param x: número a comparar
		\post El valor devuelto es verdadero si  el  polinomio  no  tiene  un  único  monomio  que  es  igual  a “x”
		\post El valor devuelto es falso, en caso contrario
		\return bool
	*/
	inline bool operator!=(ed::Polinomio const & p1, double const & x){
		return !(p1==x);
	}

	/*!
		\brief 	Comprueba  si  el  polinomio  “p”  no  es  igual  al  número  “x”,  es  decir,  si  el polinomio “p” no tiene un único monomio que es igual a “x”
		\note función inline
		\param x: número a comparar
		\param p1: polinomio a comparar
		\post El valor devuelto es verdadero si  el  polinomio  no  tiene  un  único  monomio  que  es  igual  a “x”
		\post El valor devuelto es falso, en caso contrario
		\return bool
	*/
	inline bool operator!=(double const &x, ed:: Polinomio const &p1){
		return !(p1==x);
	}


//////////////////////////////////////////////////////////////////////////////////////

	//! \name Operadores unarios

	/*!
		\brief Devuelve una copia del Polinomio “p”: +p
		\note función inline
		\param p: polinomio
		\post El polinomio devuelto es igual al polinomio “p”, es decir, tiene los mismos monomios
		\return Polinomio
	*/
	inline	ed::Polinomio & operator+(ed::Polinomio & p){
		Polinomio *nuevo = new ed::Polinomio(p);
		return *nuevo;
	}

	/*!
		\brief Devuelve el opuesto del Polinomio “p”: -p
		\param p: polinomio
		\post El  polinomio  devuelto  tiene  todos  sus  monomios  opuestos,  es  decir,  el mismo grado pero su coeficiente opuesto.
		\return Polinomio
	*/
	ed::Polinomio & operator-(ed::Polinomio const & p);


//////////////////////////////////////////////////////////////////////////////////////

	//! \name Operadores binarios de la suma

	/*!
		\brief Devuelve otro polinomio que es la suma de dos polinomios:  p1 + p2
		\note función inline
		\param p1: polinomio a sumar 1
		\param p2: polinomio a sumar 2
		\return Polinomio
	*/
		inline ed::Polinomio & operator+(ed::Polinomio const &p1,  ed::Polinomio const &p2){
			Polinomio aux(p1);
			aux+=p2;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		/*!
			\brief Devuelve otro polinomio que es la suma de un polinomio y un monomio.
			\note función inline
			\param p: polinomio a sumar
			\param m: monomio a sumar
			\return Polinomio
		*/
		inline ed::Polinomio & operator+(ed::Polinomio const &p, ed::Monomio const &m){
			Polinomio aux;
			aux=m;
			aux+=p;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		/*!
			\brief Devuelve otro polinomio que es la suma de un polinomio y un monomio.
			\note función inline
			\param p: polinomio a sumar
			\param m: monomio a sumar
			\return Polinomio
		*/

		inline ed::Polinomio & operator+(ed::Monomio const &m, ed::Polinomio const &p){
			Polinomio aux;
			aux=m;
			aux+=p;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		/*!
			\brief Devuelve otro polinomio que es la suma de un polinomio y un número real.
			\note función inline
			\param p: polinomio a sumar
			\param x: numero a sumar
			\return Polinomio
		*/
		inline ed::Polinomio & operator+(ed::Polinomio const &p, double const &x){
			Monomio m(x);
			Polinomio aux;
			aux=m;
			aux+=p;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		/*!
			\brief Devuelve otro polinomio que es la suma de un polinomio y un número real.
			\note función inline
			\param p: polinomio a sumar
			\param x: numero a sumar
			\return Polinomio
		*/
		inline ed::Polinomio & operator+(double const &x, ed::Polinomio const &p){
			Monomio m(x);
			Polinomio aux;
			aux=m;
			aux+=p;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		//////////////////////////////////////////////////////////////////////////////////////

		//! \name Operadores binarios de la resta

		/*!
		\brief Devuelve otro polinomio que es la resta de dos polinomios:  p1 -p2
		\note función inline
		\param p1: polinomio a restar 1
		\param p2: polinomio a restar 2
		\return Polinomio
		*/
		inline ed::Polinomio & operator-(ed::Polinomio const &p1,  ed::Polinomio const &p2){
			Polinomio aux(p1);
			aux-=p2;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		/*!
			\brief Devuelve otro polinomio que es la resta de un polinomio y un monomio.
			\note función inline
			\param p: polinomio a restar
			\param m: monomio a resta
			\return Polinomio
		*/
		inline ed::Polinomio & operator-(ed::Polinomio const &p, ed::Monomio const &m){
			Polinomio aux(p);
			Polinomio aux2;
			aux2=m;
			aux-=aux2;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		/*!
			\brief Devuelve otro polinomio que es la resta de un polinomio y un monomio.
			\note función inline
			\param p: polinomio a restar
			\param m: monomio a resta
			\return Polinomio
		*/
		inline ed::Polinomio & operator-(ed::Monomio const &m, ed::Polinomio const &p){
			Polinomio aux;
			aux=m;
			aux-=p;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		/*!
			\brief Devuelve otro polinomio que es la resta de un polinomio y un número
			\note función inline
			\param p: polinomio a restar
			\param x: número a resta
			\return Polinomio
		*/
		inline ed::Polinomio & operator-(ed::Polinomio const &p, double const &x){
			Monomio m(x);
			Polinomio aux(p);
			Polinomio aux2;
			aux2=m;
			aux-=aux2;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		/*!
			\brief Devuelve otro polinomio que es la resta de un polinomio y un número
			\note función inline
			\param p: polinomio a restar
			\param x: número a resta
			\return Polinomio
		*/
		inline ed::Polinomio & operator-(double const &x, ed::Polinomio const &p){
			Monomio m(x);
			Polinomio aux;
			aux=m;
			aux-=p;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		//////////////////////////////////////////////////////////////////////////////////////

		//! \name Operadores binarios de la multiplicación

		/*!
			\brief Devuelve otro polinomio que es la multiplicación de dos polinomios:  p1 * p2
			\param p1: polinomio a multiplicar 1
			\param p2: polinomio a multiplicar 2
			\return Polinomio
		*/
	 ed::Polinomio & operator*(ed::Polinomio const &p1,  ed::Polinomio const &p2);

		/*!
			\brief Devuelve  otro  polinomio  que  es  la  multiplicación  de  un  polinomio  y  un monomio.
			\note función inline
			\param p: polinomio a multiplicar
			\param m: monomio a multiplicar
			\return Polinomio
		*/
		inline ed::Polinomio & operator*(ed::Polinomio const &p, ed::Monomio const &m){
			Polinomio aux;
			aux=m;
			aux*=p;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		/*!
			\brief Devuelve  otro  polinomio  que  es  la  multiplicación  de  un  polinomio  y  un monomio.
			\note función inline
			\param p: polinomio a multiplicar
			\param m: monomio a multiplicar
			\return Polinomio
		*/
		inline ed::Polinomio & operator*(ed::Monomio const &m, ed::Polinomio const &p){
			Polinomio aux;
			aux=m;
			aux*=p;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		/*!
			\brief Devuelve  otro  polinomio  que  es  la  multiplicación  de  un  polinomio  y  un número real
			\note función inline
			\param p: polinomio a multiplicar
			\param x: numero a multiplicar
			\return Polinomio
		*/
		inline ed::Polinomio & operator*(ed::Polinomio const &p, double const &x){
			Monomio m(x);
			Polinomio aux;
			aux=m;
			aux*=p;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		/*!
			\brief Devuelve  otro  polinomio  que  es  la  multiplicación  de  un  polinomio  y  un número real
			\note función inline
			\param p: polinomio a multiplicar
			\param x: numero a multiplicar
			\return Polinomio
		*/
		inline ed::Polinomio & operator*(double const &x, ed::Polinomio const &p){
			Monomio m(x);
			Polinomio aux;
			aux=m;
			aux*=p;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		//////////////////////////////////////////////////////////////////////////////////////

		//! \name Operadores binarios de la división

		/*!
			\brief Devuelve otro polinomio que es la división de dos polinomios:  p1 / p2
			\note función inline
			\param p1: polinomio a dividir 1
			\param p2: polinomio a dividir 2
			\pre El grado de p2es menor o igual que el grado de p1
			\return Polinomio
		*/
		inline ed::Polinomio & operator/(ed::Polinomio const &p1,  ed::Polinomio const &p2){
			#ifndef NDEBUG
				assert(!p2.esNulo() and (p2.getGrado()<=p1.getGrado()));
			#endif
			Polinomio aux(p1);
			aux/=p2;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		/*!
			\brief Devuelve otro polinomio que es la división de un polinomio y un monomio.
			\note función inline
			\param p: polinomio a dividir
			\param m: monomio a dividir
			\pre El grado del monomio es menor o igual que el grado del polinomio
			\return Polinomio
		*/
		inline ed::Polinomio & operator/(ed::Polinomio const &p, ed::Monomio const &m){
			#ifndef NDEBUG
				assert((m!=0.0) and (m.getGrado()<=p.getGrado()));
			#endif
			Polinomio aux(p);
			aux/=m;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		/*!
			\brief Devuelve otro polinomio que es la división de un polinomio y un monomio.
			\note función inline
			\param p: polinomio a dividir
			\param m: monomio a dividir
			\pre El grado del monomio es menor o igual que el grado del polinomio
			\return Polinomio
		*/
		inline ed::Polinomio & operator/(ed::Monomio const &m, ed::Polinomio const &p){
			#ifndef NDEBUG
				assert(!(p.esNulo()) and (m.getGrado()>=p.getGrado()));
			#endif
			Polinomio aux;
			aux=m;
			aux/=p;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		/*!
			\brief Devuelve otro polinomio que es la división de un polinomio y un numero.
			\note función inline
			\param p: polinomio a dividir
			\param x: numero a dividir
			\pre El grado del monomio es menor o igual que el grado del polinomio
			\return Polinomio
		*/
		inline ed::Polinomio & operator/(ed::Polinomio const &p, double const &x){
			#ifndef NDEBUG
				assert((x!=0.0));
			#endif
			Polinomio aux(p);
			aux/=x;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

		/*!
			\brief Devuelve otro polinomio que es la división de un polinomio y un numero.
			\note función inline
			\param p: polinomio a dividir
			\param x: numero a dividir
			\pre El grado del monomio es menor o igual que el grado del polinomio
			\return Polinomio
		*/
		inline ed::Polinomio & operator/(double const &x, ed::Polinomio const &p){
			#ifndef NDEBUG
				assert(!(p.esNulo()) and (p.getGrado()==0));
			#endif
			Monomio m(x);
			Polinomio aux;
			aux=m;
			aux/=p;
			Polinomio *nuevo = new ed::Polinomio(aux);
			return *nuevo;
		}

	/////////////////////////////////////////////////////////////////////////////

   //! \name Sobrecarga de los operadores de flujo de la clase Polinomio.

	 /*!
	 \brief Lee desde el flujo de entrada un polinomio
	 \param stream
	 \param p
	 \return stream
 */
    ostream &operator<<(ostream &stream, ed::Polinomio const &p);

		/*!
		\brief Escribe en el flujo de el polinomio
		\param stream
 	 	\param p
		\return Stream
	*/
    istream &operator>>(istream &stream, ed::Polinomio &p);

}  // Fin de namespace ed.

#endif // _OperadoresPolinomios_HPP_
