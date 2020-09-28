NAME=Practica1main

#
OBJECTS = $(NAME).o \
		Practica1Vectores.o \
		ClaseTiempo.o \
		sistemaEcuaciones.o \
		Practica1Matrices.o

#
CPPFLAGS = -c -g -Wall -ansi -O2

INCLUDES = Practica1Vectores.hpp  \
			sistemaEcuaciones.hpp \
			Practica1Matrices.hpp


# Macros predefinidas
#
# $@: nombre del objetivo
# $^: todas las dependencias
# $<: primera dependencia
#

all: $(NAME).exe

# Primer objetivo
$(NAME).exe: $(OBJECTS)
			@echo "Generando " $@
			@g++ $^ -o $@
#
$(NAME).o: $(NAME).cpp $(INCLUDES)
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

Practica1Vectores.o: Practica1Vectores.cpp Practica1Vectores.hpp ClaseTiempo.cpp
	@echo "Compilando " $<
	@g++ $(CPPFLAGS) $<
#
ClaseTiempo.o: ClaseTiempo.cpp
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<
#
Practica1Matrices.o: Practica1Matrices.cpp Practica1Matrices.hpp ClaseTiempo.cpp Practica1Vectores.hpp
	@echo "Compilando " $<
	@g++ $(CPPFLAGS) $<

# Borrado
.PHONY: clean
clean:
	@echo "Borrando los ficheros superfluos"
	@rm -f $(OBJECTS) *~
