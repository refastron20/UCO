PROJECT(NReinas)
set(CMAKE_CXX_FLAGS "-ggdb3 -O0")
ADD_EXECUTABLE(nReinasBLV main.cpp funcionesMedioNivel.cpp reinasBacktracking.cpp reinasLasVegas.cpp place.cpp funcionesMatematicas.cpp ClaseTiempo.cpp sistemaEcuaciones.cpp ajusteCurva.cpp)
