cmake_minimum_required(VERSION 3.15)
project(sysutil C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(sysutil
     src/main.c
     src/args.c        src/args.h
     src/users.c       src/users.h
     src/processes.c  src/processes.h
     src/help.c        src/help.h
     src/io_redirect.c src/io_redirect.h
     src/util.c        src/util.h
)
