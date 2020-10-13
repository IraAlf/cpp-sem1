cmake_minimum_required(VERSION 3.8)
project(HW1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "--coverage")
set(CMAKE_C_FLAGS "--coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -Wall -Wextra -Werror --pedantic")


include_directories(project/Alignment)

set(LIB_SOURCE_FILES
        project/Alignment/alignment.c
        project/Alignment/alignment.h
        project/Alignment/test_ali.cpp)
        
        
add_library(std_lib STATIC ${LIB_SOURCE_FILES})

# sets GTEST_INCLUDE_DIRS and GTEST_LIBRARIES
find_package(GTest REQUIRED)
# adds the gtest include directory
include_directories(${GTEST_INCLUDE_DIRS})

# query_info
add_executable(test_ali.out project/Alignment/test_ali.cpp)
target_link_libraries(test_ali.out std_lib)
# links gtest
target_link_libraries(test_ali.out ${GTEST_LIBRARIES})
target_link_libraries(test_ali.out pthread)


if(ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()


