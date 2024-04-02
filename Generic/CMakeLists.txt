cmake_minimum_required(VERSION 3.27)

project(Generic)

set(CMAKE_CXX_STANDARD 17)

add_library( ${PROJECT_NAME}
              uAux.h
              uAux.cpp )

