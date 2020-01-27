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
set(SOURCES_FILES_TESTS


        test/test_img.cpp
        )


add_executable(img_proc__test ${SOURCE_FILES} ${SOURCES_FILES_TESTS} test/main_gtest.cpp)
#add_executable(netsim__nodes__test ${SOURCE_FILES} ${SOURCES_FILES_TESTS} test/main_gtest.cpp)
target_include_directories(img_proc__test PUBLIC
        ../../googletest-master/googlemock/include
        ../../googletest-master/googletest/include
        )

add_subdirectory(googletest-master)

target_link_libraries(img_proc__test gmock)