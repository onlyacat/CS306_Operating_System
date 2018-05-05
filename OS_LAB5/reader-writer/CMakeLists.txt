cmake_minimum_required(VERSION 3.5)
project(reader_writer)
set(CMAKE_EXE_LINKER_FLAGS "-pthread")
set(CMAKE_CXX_STANDARD 11 )

add_executable(reader_writer
        Main_file.c read.h write.h)
