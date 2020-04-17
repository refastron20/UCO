#ifndef  ENTERO_HPP
#define ENTERO_HPP

#include <string>
#include <iostream>

using namespace std;

class Entero{
private:
string entero_;
unsigned int tamMax_=4;

inline void setEntero(int entero){entero_=to_string(entero);};
inline void setEntero(string entero){entero_=entero;};
inline string getEntero() const {return entero_;};
inline unsigned int getTamMax() const {return tamMax_;};

public:
Entero &operator =(const int &n);
Entero &operator *=(const Entero &n);
friend Entero &operator *(const Entero &n1,const Entero &n2);
friend Entero &operator +(const Entero &n);
friend Entero &operator -(const Entero &n);
Entero &operator +=(const Entero &n);
friend Entero &operator +(const Entero &n1,const Entero &n2);
Entero &operator -=(const Entero &n);
friend Entero &operator -(const Entero &n1,const Entero &n2);
friend istream &operator>>(istream &stream, Entero &n);
friend ostream &operator<<(ostream &stream, const Entero &n);
Entero factorial();
Entero multiplicar(const Entero &n);

};

#endif
