cmake_minimum_required(VERSION 3.21)
project(RTI)

set(CMAKE_EXE_LINKER_FLAGS "-static")

set(CMAKE_CXX_STANDARD 20)

add_executable(
        RTI main.cpp
        Application.cpp
        Application.hpp
        Tri.hpp
        Vector3.cpp Vector3.hpp Math.hpp Physics.hpp)

