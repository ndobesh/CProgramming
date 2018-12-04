cmake_minimum_required(VERSION 3.12)
project(CProgramming C)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES
        DatabaseClient.c
        DatabaseServer.c
        util.c
        util.h)

include_directories(.)

add_executable(CProgramming "Homework 5/DatabaseServer.c" "Homework 5/DatabaseClient.c")