cmake_minimum_required(VERSION 3.2)
project(cpp_template)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Cpp_Template ${SOURCE_FILES} Graphes.h Sommets.h Aretes.h Molecules.h
Molecules.cpp Atomes.h Atomes.cpp Liaisons.h Liaisons.cpp Reseaux.h Reseaux.cpp Noeuds.h Noeuds.cpp Liens.h Liens.cpp includes.h)