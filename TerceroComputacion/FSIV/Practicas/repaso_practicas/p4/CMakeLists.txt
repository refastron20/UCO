CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(minitutorial_opencv)
FIND_PACKAGE(OpenCV 	REQUIRED )
LINK_LIBRARIES(${OpenCV_LIBS})
include_directories ("${OpenCV_INCLUDE_DIRS}")
set(CMAKE_CXX_FLAGS "-ggdb3 -O0")


add_executable(Practica4 Practica4.cpp)
add_executable(Calibrate calibrate.cpp)
