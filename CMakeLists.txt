cmake_minimum_required(VERSION 3.15)
project(img_proc)

set(CMAKE_CXX_STANDARD 17)

add_executable(img_proc main.cpp)

add_compile_options( -Wno-multichar)

include_directories(
        include
)

set(SOURCE_FILES
       src/bitmap.c
        src/improc.cpp
        )


add_executable(img_proc__debug ${SOURCE_FILES} ../main.cpp)
