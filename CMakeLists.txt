cmake_minimum_required(VERSION 3.23)
project(DiveDB_)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static")
add_executable(DiveDB_
        CLI/src/dabi.cpp)
set(Headers DiveDB_CLI/src/dabi_parser.h)