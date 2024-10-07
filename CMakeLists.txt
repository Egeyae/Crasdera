cmake_minimum_required(VERSION 3.29)
project(Crasdera C)

set(CMAKE_C_STANDARD 11)

add_executable(Crasdera
    src/main.c
        src/logging.c
        src/logging.h
        src/level.c
        src/level.h
)
