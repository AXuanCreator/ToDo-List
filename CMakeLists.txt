cmake_minimum_required(VERSION 3.25)
project(ToDo_List)

set(CMAKE_CXX_STANDARD 17)

add_executable(ToDo_List
        src/main.cpp src/file.h src/consoleset.cpp src/consoleset.h src/operation.cpp src/operation.h src/file.cpp)
