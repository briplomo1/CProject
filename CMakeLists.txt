cmake_minimum_required(VERSION 3.30)
project(CProject)

set(CMAKE_C_STANDARD 99)

add_executable(CProject main.c
        functions.c
)
