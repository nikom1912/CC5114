cmake_minimum_required(VERSION 3.13.2)
project("Redes Neuronales")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")



#find_package (PkgConfig REQUIRED)
#find_package (OpenGL REQUIRED)
#find_package (GLUT REQUIRED)
#find_package(PythonLibs REQUIRED)
#include_directories(${PYTHON_INCLUDE_DIRS}
#        ${LIBRARY_OUTPUT_PATH})
#
#
#
#include_directories(${OPENGL_INCLUDE_DIR}  ${GLUT_INCLUDE_DIRS})


SET(MAIN_SET
        Layer.h
        NPerceptron.h
        NPerceptron.cpp
        SigmoidNeuron.h
        SigmoidNeuron.cpp
        RedNeuronal.h
        RedNeuronal.cpp
        Funcion.h
        Funcion.cpp
        LearningPerceptron.cpp
        LearningPerceptron.h
        )

add_executable(Red main.cpp ${MAIN_SET})
add_executable(Tester main2.cpp ${MAIN_SET})
