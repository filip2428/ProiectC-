cmake_minimum_required(VERSION 3.29)
project(ProiectC_)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(ProiectC_
    Elev.cpp
    Elev.h
    main.cpp
        Absente.cpp
        Absente.h
        Materie.cpp
        Materie.h
        IO.cpp
        IO.h
)
