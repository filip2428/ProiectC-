cmake_minimum_required(VERSION 3.29)
project(ProiectC_)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(ProiectC_
    main.cpp
    src/Elev.cpp
    src/Absente.cpp
    src/Materie.cpp
    src/Nota.cpp
    src/IO.cpp
)
