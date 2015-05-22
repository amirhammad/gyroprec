cmake_minimum_required(VERSION 2.4)
SET(outputname simseg)
project(${outputname})
SET(CMAKE_BUILD_TYPE Debug)
SET(out_HEADERS 
  glw.h
  gui.h
  gyroskop.h
  gyroskopnewton.h
  )
SET(out_SOURCES
  glw.cpp
  gui.cpp
  gyroskop.cpp
  gyroskopnewton.cpp
  main.cpp
  )
#QT
find_package(Qt COMPONENTS QtCore QtOpenGL REQUIRED)

SET(QT_USE_QTOPENGL TRUE)
INCLUDE(${QT_USE_FILE})
include_directories(${QT_INCLUDES})
QT4_WRAP_CPP(out_HEADERS_MOC ${out_HEADERS})
ADD_DEFINITIONS(${QT_DEFINITIONS})

add_executable(${outputname} ${out_SOURCES} ${out_HEADERS_MOC})
target_link_libraries(${outputname} ${QT_LIBRARIES} -lglut -lGLU -lGL)

