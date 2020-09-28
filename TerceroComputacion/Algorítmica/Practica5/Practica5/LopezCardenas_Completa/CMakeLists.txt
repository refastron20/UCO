PROJECT( PolygonalApproximation )
ADD_EXECUTABLE(main.x main.cpp algorithm.cpp digitalcurve.cpp suppressioncollinearpointsmethod.cpp dynamicprogrammingmethod.cpp point.cpp line.cpp)

#set(CMAKE_CXX_FLAGS "-g")