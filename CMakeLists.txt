cmake_minimum_required(VERSION 3.28)
project(MiniSGBDR C)

set(CMAKE_C_STANDARD 11)

add_executable(MiniSGBDR main.c
        table.c
        table.h
        commandes.h
        commandes.c
)
