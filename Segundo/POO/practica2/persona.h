#ifndef PERSONA_H
#define PERSONA_H

#include <string>

using namespace std;
class Persona{
private:
 string DNI_;
 string nombre_;
 string apellidos_;
 string direccion_;
 string localidad_;
 string provincia_;
 string pais_;
 int edad_;
public:
	inline Persona(string DNI, string nombre="",string apellidos="",int edad=0,string direccion="",
		           string localidad="",string provincia="",string pais="")
	               {DNI_=DNI; nombre_=nombre;apellidos_=apellidos;edad_=edad; direccion_=direccion; localidad_=localidad;
	                provincia_=provincia; pais_=pais;}
	inline void setDNI(string DNI){if(islower(DNI[9])){toupper(DNI[9]);}DNI_=DNI;}
	inline string getDNI() const {return DNI_;}
	inline void setNombre(string nombre){nombre_=nombre;}
	inline string getNombre() const {return nombre_;}
	inline void setApellidos(string apellidos){apellidos_=apellidos;}
	inline string getApellidos() const {return apellidos_;}
	inline void setDireccion(string direccion){direccion_=direccion;}
	inline string getDireccion() const {return direccion_;}
	inline void setLocalidad(string localidad){localidad_=localidad;}
	inline string getLocalidad() const {return localidad_;}
	inline void setProvincia(string provincia){provincia_=provincia;}
	inline string getProvincia() const {return provincia_;}
	inline void setPais(string pais){pais_=pais;}
	inline string getPais() const {return pais_;}
	inline bool setEdad(int edad){if(edad>=0){edad_=edad; return true;}else{return false;}}
	inline int getEdad() const {return edad_;}
	inline bool mayor() const {if(edad_>=18){return true;}else{return false;}}
	inline string getApellidosyNombre() const {return apellidos_+", "+nombre_;}
};

#endif
