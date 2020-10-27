
cmake_minimum_required(VERSION 3.9.2)

project(DynLib)

set (CMAKE_C_STANDARD 99)

set(SOURCES src/find_max_paral.c src/utils.c)
set(HEADERS ../headers/find_max_paral.h ../headers/utils.h)

add_library(dn_lib SHARED ${SOURCES} ${HEADERS})
target_include_directories(dn_lib PUBLIC .)
