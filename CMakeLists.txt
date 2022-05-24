cmake_minimum_required(VERSION 3.21)
project(SDA_Colectie_ABC)

set(CMAKE_CXX_STANDARD 14)

add_executable(SDA_Colectie_ABC App.cpp Colectie.h Colectie.cpp IteratorColectie.h IteratorColectie.cpp
        TestScurt.h TestScurt.cpp TestExtins.h TestExtins.cpp)
