cmake_minimum_required(VERSION 3.12)
project(CProgramming C)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES
        "DatabaseClient.c"
        "DatabaseServer.c"
        "util.c"
        "util.h")

include_directories(Homework 5)

add_executable(Server "Homework 5/DatabaseServer.c")
add_executable(Client "Homework 5/DatabaseClient.c")
add_executable(Test "Test/ResponeTest.c")