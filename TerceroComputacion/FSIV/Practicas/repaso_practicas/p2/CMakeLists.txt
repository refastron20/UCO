CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(minitutorial_opencv)
FIND_PACKAGE(OpenCV 	REQUIRED )
LINK_LIBRARIES(${OpenCV_LIBS})
include_directories ("${OpenCV_INCLUDE_DIRS}")



add_executable(processImg main.cpp)
