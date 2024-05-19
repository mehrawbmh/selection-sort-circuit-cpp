cmake_minimum_required(VERSION 3.28)
project(CA4)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        CA4
        classVectorPrimitives.cpp
        classVectorPrimitives.h
        utilityFunctions.cpp
        utilityFunctions.h
        main.cpp
        datapath.hpp
        datapath.cpp
        controller.hpp
        controller.cpp
        ssc.hpp
        ssc.cpp
)
