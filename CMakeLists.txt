cmake_minimum_required(VERSION 3.29)
project(ProiectC_)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

set(SOURCES
    src/Elev.cpp
    src/Absente.cpp
    src/Materie.cpp
    src/Nota.cpp
    src/IO.cpp
)

add_executable(app1 app1.cpp ${SOURCES})
add_executable(app2 app2.cpp ${SOURCES})
