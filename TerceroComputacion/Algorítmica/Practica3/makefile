NAME=main

#
OBJECTS = $(NAME).o \
					Entero.o

#
CPPFLAGS = -c -g -Wall -ansi -O2 -std=c++11

INCLUDES = Entero.hpp


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

Entero.o: Entero.cpp Entero.hpp
			@echo "Compilando " $<
			@g++ $(CPPFLAGS) $<

# Borrado
.PHONY: clean
clean:
	@echo "Borrando los ficheros superfluos"
	@rm -f $(OBJECTS) *~
