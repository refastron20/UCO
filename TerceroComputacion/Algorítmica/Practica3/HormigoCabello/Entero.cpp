#include "Entero.hpp"
#include <cassert>
#include <iostream>
#include <cmath>


void agregarCerosDelante(std::string &c, int nCeros)
{
	int n, numeroCaracteres;
	std::string nuevaCadena;

	n = c.size();
	numeroCaracteres = n + nCeros;

	nuevaCadena.reserve(numeroCaracteres);

	for (int i = 0; i < nCeros; i++) {
		nuevaCadena.push_back('0');
	}
	for (unsigned int i = 0; i < c.size(); i++) {
		if (c[i]=='-') {
			nuevaCadena.push_back('0');
		}else{
			nuevaCadena.push_back(c[i]);
		}
	}

	c = nuevaCadena;
}

void agregarCerosFinal(std::string &c, int nCeros)
{
	for(int i = 0; i < nCeros; i++) //Se agregan ceros al final
		c.push_back('0');
}

void quitarCerosNoSignificativos(std::string &c)
{
	int i=0,salir=0;
	while (salir!=1) {
		if (c[i]=='0') {
			i++;
		}else{
			salir=1;
		}
	}
	c=c.substr(i,c.size());
}

Entero &Entero::operator =(const int &n){
  this->setEntero(n);
  return *this;
}

Entero &Entero::operator *=(const Entero &n){
  *this=*this*n;
  return *this;
}

Entero &operator *(const Entero &n1,const Entero &n2){
  Entero w,x,y,z;
  Entero r,p,q;
  std::string u=n1.getEntero();
  std::string v=n2.getEntero();
  Entero *aux= new Entero();
  if (u.size()<=n1.getTamMax() and v.size()<=n1.getTamMax()) {
    aux->setEntero(atoi(u.c_str())*atoi(v.c_str()));
    return *aux;
  }
  if (u.size()>v.size()) {
    agregarCerosDelante(v,(u.size()-v.size()));
  }else if(u.size()<v.size()){
    agregarCerosDelante(u,(v.size()-u.size()));
  }
  int s=u.size()/2;
	if (u.size()%2!=0) {
		w.setEntero(u.substr(0,s+1));
		x.setEntero(u.substr(s+1,u.size()));
		y.setEntero(v.substr(0,s+1));
		z.setEntero(v.substr(s+1,v.size()));
	}else{
	  w.setEntero(u.substr(0,s));
	  x.setEntero(u.substr(s,u.size()));
	  y.setEntero(v.substr(0,s));
	  z.setEntero(v.substr(s,v.size()));
	}
  r=(w+x)*(y+z);
  p=w*y;
  q=x*z;
	std::string cadenaAux;
	*aux=(r-p-q);
	cadenaAux=aux->getEntero();
	agregarCerosFinal(cadenaAux,(s));
	aux->setEntero(cadenaAux);
	cadenaAux=p.getEntero();
	agregarCerosFinal(cadenaAux,(2*s));
	p.setEntero(cadenaAux);
  *aux=(p+(*aux)+q);
	cadenaAux=aux->getEntero();
	quitarCerosNoSignificativos(cadenaAux);
	aux->setEntero(cadenaAux);
  return *aux;
}

Entero &Entero::operator +=(const Entero &n){
  *this=*this+n;
  return *this;
}

Entero &operator +(const Entero &n1,const Entero &n2){
	int n,suma,acarreo=0;
	std::string u=n1.getEntero(),v=n2.getEntero();
  if (u.size()>=v.size()) {
  	n=u.size();
		agregarCerosDelante(v,u.size()-v.size());
  }else{
		n=v.size();
		agregarCerosDelante(u,v.size()-u.size());
	}
	std::string resultado;
	resultado.resize(n);
	for (int i = n-1; i >=0; i--) {
		int a,b;
		a= v[i] - '0';
		b= u[i] - '0';
		suma=a+b+acarreo;
		if (suma<10){
			resultado[i]='0'+suma;
			acarreo=0;
		}else{
			resultado[i]='0'+(suma%10);
			acarreo=1;
		}
	}

	if (acarreo==1) {
		resultado.resize(resultado.size()+1);
		for (int i =resultado.size()-1; i > 0; i--) {
			resultado[i]=resultado[i-1];
		}
		resultado[0]='1';
	}

  Entero *res= new Entero();
  res->setEntero(resultado);
  return *res;
}

Entero &Entero::operator -=(const Entero &n){
  *this=*this-n;
  return *this;
}

Entero &operator -(const Entero &n1,const Entero &n2){
	int n,resta,acarreo=0;
	std::string u=n1.getEntero(),v=n2.getEntero();
	if (u.size()>=v.size()) {
		n=u.size();
		agregarCerosDelante(v,u.size()-v.size());
	}else{
		n=v.size();
		agregarCerosDelante(u,v.size()-u.size());
	}

	std::string resultado;
	resultado.resize(n);

	int a,b;
	for (int i = n-1; i >=0; i--) {
		a= u[i] - '0';
		b= v[i] - '0';
		b+=acarreo;
		if (a>=b) {
			resta=a-b;
			acarreo=0;
		}else{
			resta=(10+a)-b;
			acarreo=1;
		}
		resultado[i]='0'+resta;
	}

	if (resultado.size()>1) {
		quitarCerosNoSignificativos(resultado);
	}

	a= v[0] - '0';
	b= u[0] - '0';
	if (u.size()<v.size() or (u.size()==v.size() and b<a)) {
		resultado.resize(resultado.size()+1);
		for (int i =resultado.size()-1; i > 0; i--) {
			resultado[i]=resultado[i-1];
		}
		resultado[0]='-';
	}

	Entero *res= new Entero();
	res->setEntero(resultado);
	return *res;
}

istream &operator>>(istream &stream, Entero &n){
  string m;
  stream>>m;
  n.setEntero(m);
  return stream;
}

ostream &operator<<(ostream &stream,const Entero &n){
  stream<<n.getEntero();
  return stream;
}

Entero Entero::factorial(){
	Entero copia=*this;
	Entero *nuevo= new Entero();
	if (this->getEntero().size()==1 and this->getEntero()[0]=='1') {
		nuevo->setEntero(1);
		return *nuevo;
	}
	Entero aux;
	aux.setEntero(1);
	*nuevo=copia*(copia-aux).factorial();
	return *nuevo;
}
