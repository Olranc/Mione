cmake_minimum_required(VERSION 3.28)
project(Mione C)

set(CMAKE_C_STANDARD 11)

add_executable(Mione main.c
        FILE_TO_CASE_OBJECTS.h
        OBJECTS.h)
