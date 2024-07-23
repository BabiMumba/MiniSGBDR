cmake_minimum_required(VERSION 3.28)
project(MiniSGBDR C)

set(CMAKE_C_STANDARD 11)

add_executable(MiniSGBDR main.c
        data_types.c
        data_types.h
        table.c
        table.h
        query_processor.c
        query_processor.h
        storage_manager.c
        storage_manager.h
        menu.c
        menu.h)
