cmake_minimum_required(VERSION 3.5)
project(OS_LAB6)
set(CMAKE_EXE_LINKER_FLAGS "-pthread")
set(CMAKE_CXX_STANDARD 11 )

add_executable(OS_LAB6 mm.cpp)