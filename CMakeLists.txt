cmake_minimum_required(VERSION 3.12)
project(CProgramming C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -ansi -pedantic")

set(SOURCE_FILES
        "DatabaseClient.c"
        "DatabaseServer.c"
        "util.c"
        "util.h"
        "Test/student.h")

include_directories(Homework 5
        C:/Users/Nahtan/Downloads/L23-OtherTopics)

add_executable(Server "Homework 5/DatabaseServer.c")
add_executable(Client "Homework 5/DatabaseClient.c")
add_executable(Test "Test/ResponeTest.c")
add_executable(TestServer "Test/TestServer.c")
add_executable(TestClient "Test/TestClient.c")
