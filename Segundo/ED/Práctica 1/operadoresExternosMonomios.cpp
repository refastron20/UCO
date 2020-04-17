/*!
   \file  operadoresExternosMonomios.cpp
	\brief Ficheros con el código de los operadores externos de la clase Monomio
*/


//  Ficheros de cabecera
#include <iostream>

#include "operadoresExternosMonomios.hpp"


//  Se incluyen los operadores sobrecargados dentro del espacio de nombres ed
namespace ed
{
	// Operadores de igualdad

	bool operator==(ed::Monomio const & m1, ed::Monomio const & m2)
	{
		if((std::abs(m1.getCoeficiente()-m2.getCoeficiente())<COTA_ERROR)&&(m1.getGrado()==m2.getGrado())){
			#ifndef NDEBUG
				assert(m1.getCoeficiente()==m2.getCoeficiente());
				assert(m1.getGrado()==m2.getGrado());
				assert(std::abs(m1.getCoeficiente()-m2.getCoeficiente())<COTA_ERROR);
			#endif
			return true;
		}else{
			#ifndef NDEBUG
				assert((m1.getCoeficiente()!=m2.getCoeficiente()||(m1.getGrado()!=m2.getGrado())));
			#endif
			return false;
		}
	}

	bool operator==(ed::Monomio const & m1, double const &x)
	{
		ed::Monomio aux(x,0);
		return (m1==aux);
	}

	bool operator==(double const &x, ed::Monomio const & m1)
	{
		return (m1==x);
	}

	// Operadores de desigualdad

	// COMPLETAR
	bool operator!=(ed::Monomio const & m1, ed::Monomio const & m2)
	{
		return !(m1==m2);
	}

	bool operator!=(ed::Monomio const & m1, double const &x)
	{
		return !(m1==x);
	}

	bool operator!=(double const &x, ed::Monomio const & m1)
	{
		return (m1!=x);
	}

	////////////////////////////////////////////////////////////

	// Operadores unarios prefijos

	// COMPLETAR
	ed::Monomio & operator+(ed::Monomio const & m)
	{
		ed::Monomio *nuevo = new ed::Monomio();
		*nuevo=m;
		#ifndef NDEBUG
			assert(std::abs(m.getCoeficiente()-nuevo->getCoeficiente())<COTA_ERROR);
			assert((m.getCoeficiente()==nuevo->getCoeficiente())&&(m.getGrado()==nuevo->getGrado()));
		#endif
		return *nuevo;
	}

	ed::Monomio & operator-(ed::Monomio const & m){
			ed::Monomio *nuevo = new ed::Monomio();
			nuevo->setGrado(m.getGrado());
			nuevo->setCoeficiente(-(m.getCoeficiente()));
			#ifndef NDEBUG
				assert(std::abs(m.getCoeficiente()+nuevo->getCoeficiente())<COTA_ERROR);
				assert((m.getCoeficiente()==-(nuevo->getCoeficiente()))&&(m.getGrado()==nuevo->getGrado()));
			#endif
			return *nuevo;
		}

	////////////////////////////////////////////////////////////
	// Operadores aritméticos binarios

	// Suma
	ed::Monomio & operator+ (ed::Monomio const &m1, ed::Monomio const &m2)
	{
		#ifndef NDEBUG
			assert(m1.getGrado()==m2.getGrado());
		#endif
		ed::Monomio *nuevo = new ed::Monomio();
		*nuevo=m1;
		*nuevo+=m2;
		return *nuevo;
	}


	////////////
	// Resta

	ed::Monomio & operator- (ed::Monomio const &m1, ed::Monomio const &m2)
	{
		#ifndef NDEBUG
			assert(m1.getGrado()==m2.getGrado());
		#endif
		ed::Monomio *nuevo = new ed::Monomio();
		*nuevo=m1;
		*nuevo-=m2;
		return *nuevo;
	}


	//////////////////
	// Multiplicación

	ed::Monomio & operator* (ed::Monomio const &m1, ed::Monomio const &m2)
	{
		#ifndef NDEBUG
			assert(m1.getGrado()==m2.getGrado());
		#endif
		ed::Monomio *nuevo = new ed::Monomio();
		*nuevo=m1;
		*nuevo*=m2;
		return *nuevo;
	}

	ed::Monomio & operator* (ed::Monomio const &m, double const &x)
	{
		ed::Monomio aux(x,0);
		return m*aux;
	}

	ed::Monomio & operator* (double const &x, ed::Monomio const &m)
	{
		return m*x;
	}

	////////////
	// División


		ed::Monomio & operator/ (ed::Monomio const &m1, ed::Monomio const &m2)
		{
			#ifndef NDEBUG
				assert(m1.getGrado()==m2.getGrado());
			#endif
			ed::Monomio *nuevo = new ed::Monomio();
			*nuevo=m1;
			*nuevo/=m2;
			return *nuevo;
		}

		ed::Monomio & operator/ (ed::Monomio const &m, double const &x)
		{
			ed::Monomio aux(x,0);
			return m/aux;
		}

		ed::Monomio & operator/ (double const &x, ed::Monomio const &m)
		{
			ed::Monomio aux;
			aux=x;
			return aux/m;
		}


	/////////////////////////////////////////////////////////////////////////////

	//  Sobrecarga del operador de entrada
	istream &operator>>(istream &stream, ed::Monomio &m)
	{
		double coeficiente;
		int grado;
		stream>>coeficiente>>grado;
		m.setGrado(grado);
		m.setCoeficiente(coeficiente);
		return stream;
	}


	//  Sobrecarga del operador de salida
	ostream &operator<<(ostream &stream, ed::Monomio const &m)
	{
		stream<<m.getCoeficiente()<<" "<<m.getGrado();
		return stream;
	}


}  // namespace ed
