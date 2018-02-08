cmake_minimum_required(VERSION 3.9)
project(eineshell)

set(CMAKE_CXX_STANDARD 11)

add_executable(eineshell main.cpp src/builtin.h src/builtin.cpp src/parser.h src/parser.cpp src/execute.h src/execute.cpp src/environment.h src/environment.cpp)