cmake_minimum_required(VERSION 3.28)
project(HW5 C)

set(CMAKE_C_STANDARD 99)

add_executable(HW5 main.c
        bst.h
        bst.c
        float_rndm.h
        float_rndm.c
        iom361_r2.c
        iom361_r2.h)