cmake_minimum_required(VERSION 3.5.2)
project(eineshell)

set(CMAKE_CXX_STANDARD 11)

add_executable(eineshell main.cpp src/builtin.h src/builtin.cpp src/parser.h src/parser.cpp src/execute.h src/execute.cpp src/environment.h src/environment.cpp src/helpers.h src/helpers.cpp src/process.h src/process.cpp src/shell.h src/shell.cpp)
