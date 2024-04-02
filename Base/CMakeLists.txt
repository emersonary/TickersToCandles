cmake_minimum_required(VERSION 3.27)

project(Base)

set(CMAKE_CXX_STANDARD 17)

add_library( ${PROJECT_NAME}
        ucModelBase.h
        ucModelBase.cpp
        ucModelCad.h
        ucModelCad.cpp )

